#include <mutex>

#include "../includes/externs.h"
#include "../includes/Baker.h"
#include "../includes/PRINT.h"



using namespace std;

Baker::Baker(int id):id(id) { }

Baker::~Baker() { }

void Baker::bake_and_box(ORDER &anOrder) {
PRINT2("\n BAKER: Bake and Boxing order ", anOrder.order_number);
	Box box;
	int donuts_inserted = 0;
	while ( anOrder.number_donuts > 0 ) {
		donuts_inserted = donuts_inserted+1;

PRINT3("BAKER: Inserting Donut ", donuts_inserted, " into box");
		cout << "This is order number: " << anOrder.order_number << "\n" << endl;

		DONUT d;
		box.addDonut(d);
		anOrder.number_donuts = anOrder.number_donuts-1;

		if( donuts_inserted % DOZEN == 0 ) {
PRINT3("We've reached the maximum number of donuts in this box...", "\n", "Switching out boxes...");
                        anOrder.boxes.push_back(box);

                        Box box;
                }

	}
	anOrder.boxes.push_back(box);
}

void Baker::beBaker() {
PRINT1("\nBAKER: Okay, We are Baker now, setting everything... ");
PRINT1("BAKER: Waiting for a notification from waiter... ");

	unique_lock<mutex> lk(mutex_order_inQ);

PRINT1("BAKER: Ready to Process Orders");
	while(!b_WaiterIsFinished || !(order_in_Q.size() <= 0)) {

		if(order_in_Q.size() <= 0) {
			cv_order_inQ.wait(lk);
		}

// Use order out mutex for lockguard ...
		mutex_order_outQ.lock();

		ORDER o = order_in_Q.front();
PRINT2("BAKER: Processing Order Number ", o.order_number);
		order_in_Q.pop();

		mutex_order_outQ.unlock();

		bake_and_box(o);
PRINT2("BAKER: Processed Order ", o.order_number);
		order_out_Vector.push_back(o);
	}
}
