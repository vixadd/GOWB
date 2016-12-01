#include <mutex>

#include "../includes/externs.h"
#include "../includes/Baker.h"
#include "../includes/PRINT.h"



using namespace std;

Baker::Baker(int id):id(id) { }

Baker::~Baker() { }

void Baker::bake_and_box(ORDER &anOrder) {
PRINT2("\nBAKER: Bake and Boxing order ", anOrder.order_number);
	Box box;
	int donuts_inserted = 0;

//PRINT3("This is order number: ", anOrder.order_number, "\n");
	for(int i = 0; i < anOrder.number_donuts; i++) {
		donuts_inserted = donuts_inserted+1;

PRINT3("BAKER: Inserting Donut ", donuts_inserted, " into box");

		DONUT d;
		box.addDonut(d);
//PRINT1(box.size());
		if( donuts_inserted % DOZEN == 0 ) {
PRINT3("We've reached the maximum number of donuts in this box...", "\n", "Switching out boxes...");
                        anOrder.boxes.push_back(box);
			box.clear();
                }

	}
	anOrder.boxes.push_back(box);
//PRINT2("last box size is: ", box.size());
//PRINT2("Order Number of boxes: ", anOrder.boxes.size());
}

void Baker::beBaker() {
//PRINT1("\nBAKER: Okay, We are Baker now, setting everything... ");
PRINT1("BAKER: Waiting for a notification from waiter... ");

	unique_lock<mutex> lk(mutex_order_inQ);
	cv_order_inQ.wait(lk);

	while(!b_WaiterIsFinished || !order_in_Q.empty()) {
		if(!order_in_Q.empty()) {
			mutex_order_outQ.lock();

			ORDER o = order_in_Q.front();
			order_in_Q.pop();

			mutex_order_outQ.unlock();

			bake_and_box(o);
			order_out_Vector.push_back(o);
		}
	}
}
