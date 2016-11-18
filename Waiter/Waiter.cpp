#include <string>
#include "stdlib.h"

#include "../includes/externs.h"
#include "../includes/Waiter.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename) { }

Waiter::~Waiter() { }

/*
 * Gets the next order from the file
 * returns: status of that accessor
 */
int Waiter::getNext(ORDER &anOrder) {

	int status = myIO.getNext(anOrder);
cout << "Recieved Order: " << anOrder.order_number << endl;
	return status;
}

/*
 * Takes Orders and pushes them to an order queue
 * Uses condition variables to signal to Baker,
 * when the tickets are ready.
 */
void Waiter::beWaiter() {
cout << "Okay, We are a waiter now... Set everything right." << endl;

	ORDER o;
	int status = getNext(o);
	if(status == SUCCESS) b_WaiterIsFinished = false;
cout << "Notifying condition variable that order is in." << endl;
	cv_order_inQ.notify_all();

cout << "Preparing to make orders..." << endl;

	while ( status == SUCCESS ) {
cout << " Inserting Order " << o.order_number << " into queue " << endl;
		order_in_Q.push(o);
		status = getNext(o);
cout << "Notifying cv_order_inQ that there are jobs to do in the queue." << endl;
		cv_order_inQ.notify_all();
	}

	if(status == FAIL && !b_WaiterIsFinished) b_WaiterIsFinished = true;
}

