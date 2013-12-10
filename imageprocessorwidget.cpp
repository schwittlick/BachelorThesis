#include "imageprocessorwidget.h"

ImageProcessorWidget::ImageProcessorWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	toggleSignalMapper = new QSignalMapper( );
	downSignalMapper = new QSignalMapper();
	upSignalMapper = new QSignalMapper();
	configSignalMapper = new QSignalMapper();

	//ui.button_down_0->setGeometry( QRect( 0, 0, 40, 40 ) );


	connect( toggleSignalMapper, SIGNAL( mapped( int ) ), this, SLOT( checkBoxClickedByID( int ) ) );
	connect( toggleSignalMapper, SIGNAL( mapped( int ) ), this, SIGNAL( checkBoxClicked( int ) ) );

	connect( downSignalMapper, SIGNAL( mapped( int ) ), this, SLOT( downButtonClickedByID( int ) ) );
	connect( downSignalMapper, SIGNAL( mapped( int ) ), this, SIGNAL( downButtonClicked( int ) ) );

	connect( upSignalMapper, SIGNAL( mapped( int ) ), this, SLOT( upButtonClickedByID( int ) ) );
	connect( upSignalMapper, SIGNAL( mapped( int ) ), this, SIGNAL( upButtonClicked( int ) ) );

	connect( configSignalMapper, SIGNAL( mapped( int ) ), this, SLOT( configButtonCLickedByID( int ) ) );
	connect( configSignalMapper, SIGNAL( mapped( int ) ), this, SIGNAL( configButtonClicked( int ) ) );

	setupToggleSignals();
	setupDownSignals();
	setupUpSignals();
	setupConfigSignals();
}

ImageProcessorWidget::~ImageProcessorWidget()
{
	delete toggleSignalMapper;
	delete downSignalMapper;
	delete upSignalMapper;
	delete configSignalMapper;
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
	case 11:
		return ui.checkBox_11;
	default:
		// TODO: 
		throw 0;
		break;
	}
}

bool ImageProcessorWidget::getCheckBoxStatusByID( int id )
{
	return getCheckBoxByID( id )->isChecked();
}

void ImageProcessorWidget::setupToggleSignals()
{
	toggleSignalMapper->setMapping( ui.checkBox_0, 0 );
	connect( ui.checkBox_0, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_1, 1 );
	connect( ui.checkBox_1, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_2, 2 );
	connect( ui.checkBox_2, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_3, 3 );
	connect( ui.checkBox_3, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_4, 4 );
	connect( ui.checkBox_4, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_5, 5 );
	connect( ui.checkBox_5, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_6, 6 );
	connect( ui.checkBox_6, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_7, 7 );
	connect( ui.checkBox_7, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_8, 8 );
	connect( ui.checkBox_8, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_9, 9 );
	connect( ui.checkBox_9, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_10, 10 );
	connect( ui.checkBox_10, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
	toggleSignalMapper->setMapping( ui.checkBox_11, 11 );
	connect( ui.checkBox_11, SIGNAL( clicked( ) ),	toggleSignalMapper, SLOT( map(  ) ) );
}

void ImageProcessorWidget::setupDownSignals()
{
	downSignalMapper->setMapping( ui.button_down_0, 0 );
	connect( ui.button_down_0, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_1, 1 );
	connect( ui.button_down_1, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_2, 2 );
	connect( ui.button_down_2, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_3, 3 );
	connect( ui.button_down_3, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_4, 4 );
	connect( ui.button_down_4, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_5, 5 );
	connect( ui.button_down_5, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_6, 6 );
	connect( ui.button_down_6, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_7, 7 );
	connect( ui.button_down_7, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_8, 8 );
	connect( ui.button_down_8, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_9, 9 );
	connect( ui.button_down_9, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_10, 10 );
	connect( ui.button_down_10, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
	downSignalMapper->setMapping( ui.button_down_11, 11 );
	connect( ui.button_down_11, SIGNAL( clicked() ), downSignalMapper, SLOT( map() ) );
}

void ImageProcessorWidget::setupUpSignals()
{
	upSignalMapper->setMapping( ui.button_up_0, 0 );
	connect( ui.button_up_0, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_1, 1 );
	connect( ui.button_up_1, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_2, 2 );
	connect( ui.button_up_2, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_3, 3 );
	connect( ui.button_up_3, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_4, 4 );
	connect( ui.button_up_4, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_5, 5 );
	connect( ui.button_up_5, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_6, 6 );
	connect( ui.button_up_6, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_7, 7 );
	connect( ui.button_up_7, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_8, 8 );
	connect( ui.button_up_8, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_9, 9 );
	connect( ui.button_up_9, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_10, 10 );
	connect( ui.button_up_10, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
	upSignalMapper->setMapping( ui.button_up_11, 11 );
	connect( ui.button_up_11, SIGNAL( clicked() ), upSignalMapper, SLOT( map() ) );
}

void ImageProcessorWidget::setupConfigSignals()
{
	configSignalMapper->setMapping( ui.configButton_0, 0 );
	connect( ui.configButton_0, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_1, 1 );
	connect( ui.configButton_1, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_2, 2 );
	connect( ui.configButton_2, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_3, 3 );
	connect( ui.configButton_3, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_4, 4 );
	connect( ui.configButton_4, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_5, 5 );
	connect( ui.configButton_5, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_6, 6 );
	connect( ui.configButton_6, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_7, 7 );
	connect( ui.configButton_7, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_8, 8 );
	connect( ui.configButton_8, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_9, 9 );
	connect( ui.configButton_9, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_10, 10 );
	connect( ui.configButton_10, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
	configSignalMapper->setMapping( ui.configButton_11, 11 );
	connect( ui.configButton_11, SIGNAL( clicked() ), configSignalMapper, SLOT( map() ) );
}

void ImageProcessorWidget::upButtonClickedByID( int id )
{

}

void ImageProcessorWidget::downButtonClickedByID( int )
{

}

void ImageProcessorWidget::configButtonCLickedByID( int )
{

}

QPushButton * ImageProcessorWidget::getDownButtonById( int id )
{
	switch( id )
		{
		case 0:
			return ui.button_down_0;
			break;
		case 1:
			return ui.button_down_1;
			break;
		case 2:
			return ui.button_down_2;
			break;
		case 3:
			return ui.button_down_3;
			break;
		case 4:
			return ui.button_down_4;
			break;
		case 5:
			return ui.button_down_5;
			break;
		case 6:
			return ui.button_down_6;
			break;
		case 7:
			return ui.button_down_7;
			break;
		case 8:
			return ui.button_down_8;
			break;
		case 9:
			return ui.button_down_9;
			break;
		case 10:
			return ui.button_down_10;
			break;
		case 11:
			return ui.button_down_11;
			break;
		default:
			// lulz
			throw 0;
			break;
	}
}

QPushButton * ImageProcessorWidget::getUpButtonByID( int id )
{
	switch( id )
	{
		case 0:
			return ui.button_up_0;
			break;
		case 1:
			return ui.button_up_1;
			break;
		case 2:
			return ui.button_up_2;
			break;
		case 3:
			return ui.button_up_3;
			break;
		case 4:
			return ui.button_up_4;
			break;
		case 5:
			return ui.button_up_5;
			break;
		case 6:
			return ui.button_up_6;
			break;
		case 7:
			return ui.button_up_7;
			break;
		case 8:
			return ui.button_up_8;
			break;
		case 9:
			return ui.button_up_9;
			break;
		case 10:
			return ui.button_up_10;
			break;
		case 11:
			return ui.button_up_11;
			break;
		default:
			// luuulz
			throw 0;
			break;
	}
}

QPushButton * ImageProcessorWidget::getConfigButtonByID( int id )
{
	switch( id )
	{
		case 0:
			return ui.configButton_0;
			break;
		case 1:
			return ui.configButton_1;
			break;
		case 2:
			return ui.configButton_2;
			break;
		case 3:
			return ui.configButton_3;
			break;
		case 4:
			return ui.configButton_4;
			break;
		case 5:
			return ui.configButton_5;
			break;
		case 6:
			return ui.configButton_6;
			break;
		case 7:
			return ui.configButton_7;
			break;
		case 8:
			return ui.configButton_8;
			break;
		case 9:
			return ui.configButton_9;
			break;
		case 10:
			return ui.configButton_10;
			break;
		case 11:
			return ui.configButton_11;
			break;
		default:
			// luuulz
			throw 0;
			break;
	}
}

QLabel * ImageProcessorWidget::getLabelByID( int id )
{
	switch( id )
	{
		case 0:
			return ui.label_0;
			break;
		case 1:
			return ui.label_1;
			break;
		case 2:
			return ui.label_2;
			break;
		case 3:
			return ui.label_3;
			break;
		case 4:
			return ui.label_4;
			break;
		case 5:
			return ui.label_5;
			break;
		case 6:
			return ui.label_6;
			break;
		case 7:
			return ui.label_7;
			break;
		case 8:
			return ui.label_8;
			break;
		case 9:
			return ui.label_9;
			break;
		case 10:
			return ui.label_10;
			break;
		case 11:
			return ui.label_11;
			break;
		default:
			// luuulz
			throw 0;
			break;
	}
}
