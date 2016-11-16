#include <mutex>

#include "..\includes\Baker.h"
using namespace std;

Baker::Baker(int id):id(id) { }

Baker::~Baker() { }

void Baker::bake_and_box(ORDER &anOrder) {
	while ( anOrder.number_donuts > 0 ) {
		if( anOrder.number_donuts % DOZEN == 0 ) {
			anOrder.boxes.insert(box);
			Box box = new Box();
		}
		DONUT d;
		box.addDonut(d);
		anOrder.number_donuts = anOrder.number_donuts -1;
	}
	anOrder.boxes.insert(box);
}

void Baker::beBaker() {
	while(order_in_Q.size() > 0) {
		ORDER o = order_in_Q.front();
		order_in_Q.pop();

		//Lock it here
		bake_and_box(o);
		order_outvector.insert(o);

		// Check condition variable
	}
}
