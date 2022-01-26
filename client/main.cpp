#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <netdb.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <assert.h>
#include <inttypes.h>
#include <typeinfo>
#include <cstdio>

#include "ThreadPool.hpp"
#include "tcp.hpp"
#include "RDMA.hpp"
#include "map"
#define PORT 1
using namespace std;

std::string HostToIp(const std::string& host) {
    hostent* hostname = gethostbyname(host.c_str());
    if(hostname)
        return std::string(inet_ntoa(**(in_addr**)hostname->h_addr_list));
    return {};
}


int main(){
  
  int num_host = 2;
  string host_file = "../hostfile/hostinfo.txt";
  ThreadPool* connectionThread = new ThreadPool(num_host);
  tcp t[num_host];
  
  //Find my host number
  ifstream hostfile(host_file);
  char hostname[256];
	size_t hostnamelen = 256;
	gethostname(hostname, hostnamelen);
	string tmp(hostname);
	int hostnum = 0;
  string s;
  char buf[100];

	for(int i=0; i<num_host; i++){
		hostfile.getline(buf, 100);
		s = buf;
		if(tmp.compare(s) == 0){
			break;
		}
		hostnum++;
	}
	hostfile.close();

  //Connection TCP/IP
  hostfile.open(host_file);
  vector<char[15]> server_ip(num_host);

  for(int i=0; i<num_host; i++){
    hostfile.getline(buf, 100);
    s = buf;
    s = HostToIp(s);
    strcpy(server_ip[i], s.c_str());
    t[i].SetInfo(i, 3141592, server_ip[i], num_host, 3141592+hostnum, 1024);
    t[i].SetSocket();
    connectionThread->EnqueueJob([&t, i](){t[i].ConnectSocket();});
  }
  
  while(true){
			if(connectionThread->getJobs().empty()){
				while(true){
					if(connectionThread->checkAllThread())break;
				}
				break;
			}
	}

  /*
  0(server) --------- 1(client)
  */

  //////////////////////////////////////////////////////////////
  //Create user context -> Create protection domain -> Create completion queue -> Create queue pair -> Create buffer(Send/Recv) -> Exchange RDMA Information using TCP/IP-> Change qurer pair state 
  RDMA *rdma = new RDMA();
  
  struct ibv_context* context = rdma->createContext(); //집짓고 주소지 등록
  struct ibv_pd* protection_domain = ibv_alloc_pd(context); //법적 권리 획득
  int cq_size = 0x10;
  struct ibv_cq* completion_queue = ibv_create_cq(context, cq_size, nullptr, nullptr, 0); //발송 및 수령 확인처 생성
  struct ibv_qp* qp = rdma->createQueuePair(protection_domain, completion_queue); // 신상정보 등록
  char send_buffer[1024];
  struct ibv_mr *mr = rdma->registerMemoryRegion(protection_domain, send_buffer, sizeof(send_buffer)); // 발송 및 수령지 등록 및 고정
  
  uint16_t lid = rdma->getLocalId(context, PORT); // 내 주소지 뭡니까?
  uint32_t qp_num = rdma->getQueuePairNumber(qp); // 내 신상정보 뭡니까?

  //Send RDMA info
  std::ostringstream oss;
  oss << &send_buffer;
  t[0].SendRDMAInfo(oss.str()+"\n");
  t[0].SendRDMAInfo(to_string(mr->length)+"\n");
  t[0].SendRDMAInfo(to_string(mr->lkey)+"\n");
  t[0].SendRDMAInfo(to_string(mr->rkey)+"\n");
  t[0].SendRDMAInfo(to_string(lid)+"\n");
  t[0].SendRDMAInfo(to_string(qp_num)+"\n");

  //Read RDMA info
  map<string, string> rdmaInfo = t[0].ReadRDMAInfo();

  //Exchange queue pair state
  rdma->changeQueuePairStateToInit(qp);
  rdma->changeQueuePairStateToRTR(qp, PORT, stoi(rdmaInfo.find("qp_num")->second), stoi(rdmaInfo.find("lid")->second));
  rdma->changeQueuePairStateToRTS(qp);

  for(int i = 0; i < 1024; i++)send_buffer[i]='f';

  rdma->post_rdma_write(qp, mr, send_buffer, sizeof(char)*1024, rdmaInfo.find("addr")->second, rdmaInfo.find("rkey")->second);
  rdma->pollCompletion(completion_queue);

  ibv_destroy_qp(qp);
  ibv_destroy_cq(completion_queue);
  ibv_dereg_mr(mr);
  ibv_dealloc_pd(protection_domain);
 
  
  return 0;
}
