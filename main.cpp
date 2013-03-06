
#include <qapplication.h>

#include "DrtaMW2.h"

int main(int argc , char** argv)
{
	bool enableGui = true;
	int ret = 0;

	QApplication app( argc, argv);

	if (enableGui)
	{
		DrtaMW2 *drta = new DrtaMW2();
		app.setMainWidget( drta);

		drta -> setGeometry(0,0,640,480);
		drta -> initDrta(0);
		drta -> show();

		QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

		return app.exec();
	}


	return ret;
}
