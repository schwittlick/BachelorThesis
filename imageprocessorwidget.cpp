#include "imageprocessorwidget.h"

ImageProcessorWidget::ImageProcessorWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	signalMapper = new QSignalMapper( );

	connect( signalMapper, SIGNAL( mapped( int ) ), this, SLOT( checkBoxClickedByID( int ) ) );
	connect( signalMapper, SIGNAL( mapped( int ) ), this, SIGNAL( checkBoxClicked( int ) ) );

	signalMapper->setMapping( ui.checkBox_0, 0 );
	connect( ui.checkBox_0, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_1, 1 );
	connect( ui.checkBox_1, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_2, 2 );
	connect( ui.checkBox_2, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_3, 3 );
	connect( ui.checkBox_3, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_4, 4 );
	connect( ui.checkBox_4, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_5, 5 );
	connect( ui.checkBox_5, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_6, 6 );
	connect( ui.checkBox_6, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_7, 7 );
	connect( ui.checkBox_7, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_8, 8 );
	connect( ui.checkBox_8, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_9, 9 );
	connect( ui.checkBox_9, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	signalMapper->setMapping( ui.checkBox_10, 10 );
	connect( ui.checkBox_10, SIGNAL( clicked( ) ),	signalMapper, SLOT( map(  ) ) );
	
}

ImageProcessorWidget::~ImageProcessorWidget()
{
	if( signalMapper )
	{
		delete signalMapper;
	}
}

void ImageProcessorWidget::checkBoxClickedByID( int id )
{
	bool isChecked = getCheckBoxStatusByID( id );
	std::cout << id << "=" << isChecked << std::endl;
}

QCheckBox * ImageProcessorWidget::getCheckBoxByID( int id )
{
	switch( id )
	{
	case 0:
		return ui.checkBox_0;
		break;
	case 1:
		return ui.checkBox_1;
		break;
	case 2:
		return ui.checkBox_2;
		break;
	case 3:
		return ui.checkBox_3;
		break;
	case 4:
		return ui.checkBox_4;
		break;
	case 5:
		return ui.checkBox_5;
		break;
	case 6:
		return ui.checkBox_6;
		break;
	case 7:
		return ui.checkBox_7;
		break;
	case 8:
		return ui.checkBox_8;
		break;
	case 9:
		return ui.checkBox_9;
		break;
	case 10:
		return ui.checkBox_10;
		break;
	default:
		// TODO: 
		return ui.checkBox_1;
		break;
	}
}

bool ImageProcessorWidget::getCheckBoxStatusByID( int id )
{
	return getCheckBoxByID( id )->isChecked();
}
