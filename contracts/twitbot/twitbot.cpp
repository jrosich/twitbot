#include "twitbot.hpp"

namespace TWITBOT {
    using namespace eosio;

    void apply_transfer(const TWITBOT::transfer &msg) {
        // TODO: get memo (to know the account)
        // TODO: create database of twitter account -> amount
        print("got into apply transfer: ", msg.quantity," ", "\n");
    }

    void apply_withdrawal(const TWITBOT::withdrawal &msg) {
        // TODO: check that this is called by twitbot account
        // TODO: send amount to owner
        print("got into withdrawal: ", msg.quantity, "\n");
    }

    void apply_tipping(const TWITBOT::tipping &msg) {
        // TODO: check that this is called by twitbot account
        // TODO: check that from has balance and send it to destination
        print("got into apply tipping: ", msg.quantity, "\n");
    }
}

using namespace TWITBOT;

extern "C" {
    void init() {
        print("[TWITBOT contract] intializing\n");
    }

    void apply(uint64_t code, uint64_t action) {
        print("[TWITBOT contract] received ", name(code), "->", name(action), "\n");

        if (code == N(eos) && action == N(transfer)) {
            print("Transfer received!\n");
            //print(current_message);
            apply_transfer(current_message<TWITBOT::transfer>());
            // assert(false, "rejecting transaction!"); // How to throw an exception
        }

        if (code != N(twitbot))
            return;

        switch (action) {
            case N(withdrawal):
                print("withdrawaling ...!\n");
                apply_withdrawal(current_message<withdrawal>());
                break;
            case N(tip):
                print("tipping ...!\n");
                apply_tipping(current_message<tipping>());
                break;
            default:
                break;
        }
    }
}