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
	int status = getNext(anOrder);
	return status;
}

/*
 * Takes Orders and pushes them to an order queue
 * Uses condition variables to signal to Baker,
 * when the tickets are ready.
 */
void Waiter::beWaiter() {
	ORDER o;
	int status = getNext(o);
	if(status == SUCCESS) b_WaiterIsFinished = false;
	unique_lock<mutex> lock1(mutex_order_inQ, defer_lock);
	while ( status == SUCCESS ) {
		order_in_Q.push(o);
		status = getNext(o);
		cv_order_inQ.notify_All();
	}

	if(status == FAIL && !b_WaiterIsFinished) b_WaiterIsFinished = true;
}

