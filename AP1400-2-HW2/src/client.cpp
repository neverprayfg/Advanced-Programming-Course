#include "../include/client.h"
#include "../include/crypto.h"
#include <random>


Client::Client(std::string id, const Server& server):server(&server), id(id){
    crypto::generate_key(public_key, private_key);
}

std::string Client::get_id() const{
    return id;
}

std::string Client::get_publickey() const{
    return public_key;
}

double Client::get_wallet() const{
    return server->get_wallet(id);
}

std::string Client::sign(std::string txt) const{
    return crypto::signMessage(private_key, txt);
}

bool Client::transfer_money(std::string receiver, double value) const{
    auto ptr = server->get_client(receiver);
    if(ptr == nullptr) return false;
    std::string trx = id + '-' + receiver + '-' + std::to_string(value);
    std::string signature = crypto::signMessage(private_key, trx);
    return server->add_pending_trx(trx, signature);
}

size_t Client::generate_nonce() const{
    std::mt19937_64 rd(time(0));
    std::uniform_int_distribution<size_t> rand_device;
    return rand_device(rd);
}

