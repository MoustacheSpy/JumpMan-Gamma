
#include "stdafx.h"
#include "main_refresher.h"

int main(int argc, char* args[])
{
	Main _this;
	//_this.init();
	while (1) {
	//	printf("loop");
		_this.update();
	}
	_this.destroy();
}