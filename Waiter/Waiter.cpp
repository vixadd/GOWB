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
PRINT2("GETNEXT: Recieved Order: ", anOrder.order_number);
	return status;
}

/*
 * Takes Orders and pushes them to an order queue
 * Uses condition variables to signal to Baker,
 * when the tickets are ready.
 */
void Waiter::beWaiter() {
PRINT1("\nOkay, We are a waiter now...");

	ORDER o;
	int status = getNext(o);

	while ( status == SUCCESS ) {

PRINT3("BEWAITER: Inserting Order ", o.order_number, " into queue ");

		mutex_order_outQ.lock();
		order_in_Q.push(o);
		mutex_order_outQ.unlock();

		cv_order_inQ.notify_all();

		status = getNext(o);
	}
	b_WaiterIsFinished = true;
}

