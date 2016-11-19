#include <string>
#include "stdlib.h"

#include "..\includes\Waiter.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename) { }

Waiter::~Waiter() { }

/*
 * Gets the next order from the file
 * returns: status of that accessor
 */
int Waiter::getNext(ORDER &anOrder) {

}

/*
 * Takes Orders and pushes them to an order queue
 * Uses condition variables to signal to Baker,
 * when the tickets are ready.
 */
void Waiter::beWaiter() {

}

