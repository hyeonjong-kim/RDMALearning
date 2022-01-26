#include <infiniband/verbs.h>
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
  RDMA rdma;
  
  struct ibv_context* context = rdma.createContext();
  struct ibv_pd* protection_domain = ibv_alloc_pd(context);
  int cq_size = 0x10;
  struct ibv_cq* completion_queue = ibv_create_cq(context, cq_size, nullptr, nullptr, 0);
  struct ibv_qp* qp = rdma.createQueuePair(protection_domain, completion_queue);
  char send_buffer[1024];
  struct ibv_mr *mr = rdma.registerMemoryRegion(protection_domain, send_buffer, sizeof(send_buffer));
  uint16_t lid = rdma.getLocalId(context, PORT);
  uint32_t qp_num = rdma.getQueuePairNumber(qp);

  //Send RDMA info
  std::ostringstream oss;
  oss << &send_buffer;
  t[1].SendRDMAInfo(oss.str()+"\n");
  t[1].SendRDMAInfo(to_string(mr->length)+"\n");
  t[1].SendRDMAInfo(to_string(mr->lkey)+"\n");
  t[1].SendRDMAInfo(to_string(mr->rkey)+"\n");
  t[1].SendRDMAInfo(to_string(lid)+"\n");
  t[1].SendRDMAInfo(to_string(qp_num)+"\n");

  //Read RDMA info
  map<string, string> rdmaInfo = t[1].ReadRDMAInfo();

  //Exchange queue pair state
  rdma.changeQueuePairStateToInit(qp);
  rdma.changeQueuePairStateToRTR(qp, PORT, stoi(rdmaInfo.find("qp_num")->second), stoi(rdmaInfo.find("lid")->second));
  rdma.changeQueuePairStateToRTS(qp);

  sleep(10);
  for(int i = 0; i < 1024; i++)cout << send_buffer[i];
  
  ibv_destroy_qp(qp);
  ibv_destroy_cq(completion_queue);
  ibv_dereg_mr(mr);
  ibv_dealloc_pd(protection_domain);

  return 0;
}
