#include <string>
#include "stdlib.h"

#include "../includes/externs.h"
#include "../includes/Waiter.h"
#include "../includes/PRINT.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename) { }

Waiter::~Waiter() { }

/*
 * Gets the next order from the file
 * returns: status of that accessor
 */
int Waiter::getNext(ORDER &anOrder) {

	int status = myIO.getNext(anOrder);
PRINT2("Recieved Order: ", anOrder.order_number);
	return status;
}

/*
 * Takes Orders and pushes them to an order queue
 * Uses condition variables to signal to Baker,
 * when the tickets are ready.
 */
void Waiter::beWaiter() {
PRINT1("\nOkay, We are a waiter now... Set everything right.");

	ORDER o;
	int status = getNext(o);
	if(status == SUCCESS) b_WaiterIsFinished = false;
PRINT1("Notifying condition variable that order is in.");
	order_in_Q.push(o);

	cv_order_inQ.notify_all();

PRINT1("Preparing to make orders...");

	while ( status == SUCCESS ) {
		status = getNext(o);

PRINT3("Inserting Order ", o.order_number, " into queue ");

//		lock_guard<mutex> lock(mutex_order_outQ);
		order_in_Q.push(o);

	}

	if(status == FAIL && !b_WaiterIsFinished) b_WaiterIsFinished = true;

}

