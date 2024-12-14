#pragma once
#include <qfsm/State.h>
#include "Player.h"

// Idle state
struct Idle : public qfsm::State<Idle> {
    static void onEnter(Player& player);
};

// Walk state 
struct Walk : public qfsm::State<Walk> {
    static void onEnter(Player& player);
};

// Jump state
struct Jump : public qfsm::State<Jump> {
    static void onEnter(Player& player);
};

// Fall state
struct Fall : public qfsm::State<Fall> {
    static void onEnter(Player& player);
};

// Run state
struct Run : public qfsm::State<Run> {
    static void onEnter(Player& player);
};

// Hit state
struct Hit : public qfsm::State<Hit> {
    static void onEnter(Player& player);
    static void onExit(Player& player);
};