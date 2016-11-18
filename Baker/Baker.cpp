#include <mutex>

#include "../includes/Baker.h"
using namespace std;

Baker::Baker(int id):id(id) { }

Baker::~Baker() { }

void Baker::bake_and_box(ORDER &anOrder) {
	Box *box = new Box();
	int donuts_inserted = 0;
	while ( anOrder.number_donuts > 0 ) {
		donuts_inserted = donuts_inserted+1;

		cout << "Inserting Donut " + donuts_inserted + " into box" << endl;

		DONUT d;
		box->addDonut(d);
		anOrder.number_donuts = anOrder.number_donuts-1;

		if( donuts_inserted % DOZEN == 0 ) {
			cout << "We've reached the maximum number of donuts in this box..." << endl << "Switching out boxes..." << endl;
                        anOrder.boxes.push_back(box);
                        box = new Box();
                }

	}
	anOrder.boxes.push_back(box);
}

void Baker::beBaker() {

	unique_lock<mutex> lk(mutex_order_inQ);
	cv_order_inQ.wait(mutex_order_inQ);

	unique_lock<mutex> lk_retrieve(mutex_order_outQ);
	while(order_in_Q.size() > 0) {

		lk_retrieve.lock();

		ORDER o = order_in_Q.front();
		order_in_Q.pop();

		lk_retirieve.unlock();

		bake_and_box(o);
		order_outvector.insert(o);
	}
}
