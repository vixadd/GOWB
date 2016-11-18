#include <mutex>

#include "../includes/externs.h"
#include "../includes/Baker.h"
//#include "../include/PRINT.h"
using namespace std;

Baker::Baker(int id):id(id) { }

Baker::~Baker() { }

void Baker::bake_and_box(ORDER &anOrder) {
cout << "\n BAKER: Bake and Boxing order " << anOrder.order_number << endl;
	Box box;
	int donuts_inserted = 0;
	while ( anOrder.number_donuts > 0 ) {
		donuts_inserted = donuts_inserted+1;

		cout << "BAKER: Inserting Donut " << donuts_inserted << " into box" << endl;
		cout << "This is order number: " << anOrder.order_number << "\n" << endl;

		DONUT d;
		box.addDonut(d);
		anOrder.number_donuts = anOrder.number_donuts-1;

		if( donuts_inserted % DOZEN == 0 ) {
			cout << "We've reached the maximum number of donuts in this box..." << endl << "Switching out boxes..." << endl;
                        anOrder.boxes.push_back(box);

                        Box box;
                }

	}
	anOrder.boxes.push_back(box);
}

void Baker::beBaker() {
cout << "\n BAKER: Okay, We are Baker now, setting everything... " << endl;
cout << "BAKER: Waiting for a notification from waiter... " << endl;

	unique_lock<mutex> lk(mutex_order_inQ);
	cv_order_inQ.wait(lk, []{ return !b_WaiterIsFinished; });

cout << "BAKER: Ready to Process Orders" << endl;
	while(order_in_Q.size() > 0 || !b_WaiterIsFinished) {

// Use order out mutex for lockguard ...


		ORDER o = order_in_Q.front();
cout << "BAKER: Processing Order Number " << o.order_number << endl;
		order_in_Q.pop();

		bake_and_box(o);
cout << "BAKER: Processed Order " << o.order_number << endl;
		order_out_Vector.push_back(o);
	}
}
