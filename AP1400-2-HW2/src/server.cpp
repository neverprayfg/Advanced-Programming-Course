#include "../include/server.h"
#include "../include/crypto.h"
#include <random>
#include <regex>
#include <iostream>
#include <sstream>
#include <chrono>
std::vector<std::string> pending_trxs;
std::shared_ptr<Client> Server::add_client(std::string id){
    auto id_ptr = get_client(id);
    if(id_ptr != nullptr)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937_64 rd(seed);
        std::uniform_int_distribution<int> uniform_dist(1000, 9999);
        int pre_id = uniform_dist(rd);
        id += std::to_string(pre_id);
    }
    auto re_ptr = std::make_shared<Client>(id, *this);
    clients[re_ptr] = 5.0;
    return re_ptr;
}
                 
std::shared_ptr<Client> Server::get_client(std::string id) const{
    for(auto& i:clients)
    {
        if(i.first->get_id() == id) return i.first;
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    auto it_ptr = get_client(id);
    return clients.at(it_ptr);
}

bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
    std::regex pattern("^([^-]+)-([^-]+)-(\\d+(?:\\.\\d+)?)$");
    std::smatch match;
    if(!std::regex_match(trx, match, pattern)) throw std::runtime_error("");
    sender = match[1];
    receiver = match[2];
    value = std::stod(match[3]);
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const
{
    std::string sender{}, receiver{};
    double value;
    parse_trx(trx, sender, receiver, value);
    auto sender_ptr = get_client(sender);
    if(sender_ptr != nullptr)
    {
        std::string public_key = sender_ptr->get_publickey();
        bool isvalid = crypto::verifySignature(public_key, trx, signature);
        if(isvalid && clients.at(sender_ptr) >= value) {
            pending_trxs.push_back(trx);
            return true;
        }
    }
    return false;
}

size_t Server::mine() {
    std::string mempool{};
    for(auto& i: pending_trxs) 
    {
        mempool += i;
        std::string sender{}, receiver{};
        double value;
        parse_trx(i, sender, receiver, value);
        auto sender_ptr = get_client(sender);
        auto receiver_ptr = get_client(receiver);
        clients[sender_ptr] -= value;
        clients[receiver_ptr] += value;
    }
    while(true)
    {
        for(auto& i: clients)
        {
            size_t nonce = i.first->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(nonce));
            if(hash.substr(0, 10).find("000") != std::string::npos)
            {
                clients[i.first] += 6.25;
                std::cout << i.first->get_id();
                return nonce;
            }
        }
    }
}

void  show_pending_transactions(){

 	std::cout  <<  std::string(20, '*') <<  std::endl;
 	for(const  auto& trx : pending_trxs)
 		std::cout << trx <<  std::endl;
 	std::cout  <<  std::string(20, '*') <<  std::endl;
}

void show_wallets(const  Server& server){

 	std::cout << std::string(20, '*') << std::endl;
 	for(const auto& client: server.clients)
 		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
 	std::cout << std::string(20, '*') << std::endl;
}