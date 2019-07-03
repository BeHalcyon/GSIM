#include "mainwindow.h"
#include "define.h"

#include<QLayout>
#include<QScrollArea>
#include<QSizePolicy>
#include <QDockWidget>
#include<QFileDialog>
#include <QTabWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QMessageBox>
#include <QChartView>
#include <fstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
	colors.push_back(QColor(76, 110, 196));
	colors.push_back(QColor(96, 153, 213));
	colors.push_back(QColor(165, 165, 165));
	colors.push_back(QColor(89, 143, 33));
	colors.push_back(QColor(156, 207, 145));
	colors.push_back(QColor(237, 128, 48));
	colors.push_back(QColor(253, 195, 1));
	colors.push_back(QColor(255, 241, 194));
	colors.push_back(QColor(168, 70, 70));
	colors.push_back(QColor(211, 151, 151));
	colors.push_back(QColor(180, 163, 150));
	colors.push_back(QColor(169, 104, 54));

	featurecolors.push_back(QColor(253, 174, 97, 100));
	featurecolors.push_back(QColor(171, 221, 164, 100));
	featurecolors.push_back(QColor(43, 131, 186, 100));
	featurecolors.push_back(QColor(215, 25, 28, 100));
	featurecolors.push_back(QColor(26, 150, 65, 100));
	ui.setupUi(this);
	setWindowState(Qt::WindowMaximized);

	bicluster = new Bicluster();
	entropyviewer = new CalEntropy();

	setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

	QWidget* widget = new QWidget();
	setWidget = new SetView();
	cpWidget = new ControlPanel(setWidget);
	setViewHeader = new SetViewHeader(entropyviewer);
	scrollArea = new QScrollArea(widget);
	scrollArea->setFrameShape(QFrame::NoFrame);
	scrollArea->setWidget(setWidget);
	scrollArea->setWidgetResizable(true);
	QVBoxLayout* vboxlayout = new QVBoxLayout;
	QHBoxLayout* hboxlayout = new QHBoxLayout;
	vboxlayout->setMargin(0);
	vboxlayout->addWidget(setViewHeader);
	vboxlayout->addWidget(scrollArea);
	hboxlayout->setMargin(0);
	hboxlayout->addWidget(cpWidget);
	hboxlayout->addLayout(vboxlayout);
	widget->setLayout(hboxlayout);
	widget->setAutoFillBackground(true);
	QPalette p;
	p.setBrush(backgroundRole(), QBrush(QColor(255, 255, 255)));
	widget->setPalette(p);
	QDockWidget* dock = new QDockWidget(tr("Variate Sets"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	dock->setWidget(widget);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	//pcWidget = new ParallelCoordinate(colors);
	//QDockWidget * dock3 = new QDockWidget(tr("Parallel Coordinate"), this);
	//dock3->setWidget(pcWidget);
	//dock3->setAllowedAreas(Qt::BottomDockWidgetArea);
	//addDockWidget(Qt::BottomDockWidgetArea, dock3);

	//spWidget = new ScatterPlot(colors);
	rWidget = new RenderWidget();
	QHBoxLayout* hboxlayout2 = new QHBoxLayout;
	hboxlayout2->setMargin(0);
	//hboxlayout2->addWidget(spWidget);
	hboxlayout2->addWidget(rWidget);
	QWidget* widget2 = new QWidget();
	widget2->setLayout(hboxlayout2);
	setCentralWidget(widget2);

	tfWidget = new TF1DWidget();
	dock2 = new QDockWidget(tr("Transfer Function"), this);
	dock2->setAllowedAreas(Qt::BottomDockWidgetArea);
	dock2->setWidget(tfWidget);
	dock2->setVisible(false);
	addDockWidget(Qt::BottomDockWidgetArea, dock2);

	//distributionView = new DisDistribution();
	//dock4 = new QDockWidget(tr("Hierarchical Clustering Distance"), this);
	//dock4->setAllowedAreas(Qt::BottomDockWidgetArea);
	//dock4->setWidget(distributionView);
	//dock4->setVisible(false);
	//addDockWidget(Qt::BottomDockWidgetArea, dock4);

	renderpropertyview = new RenderPropertyWidget(rWidget);
	dock5 = new QDockWidget(tr("Render Properties"), this);
	dock5->setAllowedAreas(Qt::BottomDockWidgetArea);
	dock5->setWidget(renderpropertyview);
	dock5->setVisible(false);
	addDockWidget(Qt::BottomDockWidgetArea, dock5);

	createMenus();
	createConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::loadvolume(QStringList files)
{
	char prefix[1024];
	bool compress;
	variatenames.clear();
	for (int i = 0; i < files.size(); i++)
	{
		int s = files[i].lastIndexOf("/");
		int e = files[i].lastIndexOf(".vifo");
		variatenames << files[i].mid(s + 1, e - s - 1);
	}
	vdata.resize(files.size());
	for (int i = 0; i < files.size(); i++)
	{
		vdata[i] = new Volume();
		if (!vdata[i]->loadVolume(files.at(i))) {
			cerr << "Failed to load data" << std::endl;
			exit(1);
		}
	}

	volRegions.resize(4);
	for (int i = 0; i < volRegions.size(); i++)
	{
		volRegions[i] = new uchar[vdata[0]->getTotalSize()];
		memset(volRegions[i], 0, vdata[0]->getTotalSize() * sizeof(uchar));
	}

	emit sendData(vdata[0]);
	emit sendDatas(vdata);
}

void MainWindow::getNamesofVariates()
{
	QStringList files = QFileDialog::getOpenFileNames(
		this,
		"Select one or more files to open",
		"dataset/",
		"VariatesList (*.vifo)");
	if (files.size() == 0) return;
	QStringList currentpos;
	currentpos = files;
	loadvolume(currentpos);
}

void MainWindow::getSelectedVariatesNo(int selectedNo)
{
	emit sendData(vdata[selectedNo]);
}

void MainWindow::createMenus()
{
	loadAct = new QAction(tr("&Load..."), this);
	loadAct->setStatusTip(tr("Load Data Set"));
	connect(loadAct, SIGNAL(triggered()), this, SLOT(getNamesofVariates()));
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(loadAct);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(dock2->toggleViewAction());
	//viewMenu->addAction(dock4->toggleViewAction());
	viewMenu->addAction(dock5->toggleViewAction());

	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAct);
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Application"), tr("Co-Analysis Framework 2017.02"));
}

void MainWindow::createConnections()
{
	connect(this, SIGNAL(sendDatas(vector<Volume *>&)), entropyviewer, SLOT(setDatas(vector<Volume *>&)));
	connect(this, SIGNAL(sendDatas(vector<Volume *>&)), bicluster, SLOT(setVolDatas(vector<Volume *>&)));

	connect(bicluster, SIGNAL(sendVariateSubsets(vector<VSubset>)), setWidget, SLOT(getVariateSubsets(vector<VSubset>)));
	connect(setWidget, SIGNAL(getCorrelation(vector<int>, float&)), bicluster, SLOT(calCorrelation(vector<int>, float&)));
	connect(setWidget, SIGNAL(getCorrelationPearson(vector<int>, float&)), bicluster, SLOT(calCorrelationPearson(vector<int>, float&)));

	connect(setWidget, SIGNAL(getCoherence(vector<int>, float&)), bicluster, SLOT(calCoherence(vector<int>, float&)));
	connect(bicluster, SIGNAL(sendMaxDegree(int)), setWidget, SLOT(getMaxLevel(int)));
	connect(setWidget, SIGNAL(sendSelectedSubset(vector<int>)), bicluster, SLOT(SelectedVariatesNo(vector<int>)));
	//Debug 20180203
	connect(cpWidget->isJaccardUsed, SIGNAL(stateChanged(int)), bicluster, SLOT(setJaccardDistanceUsed(int)));

	
	connect(cpWidget->pushButton, SIGNAL(clicked()), cpWidget, SLOT(sendTextLineValue()));
	connect(cpWidget, SIGNAL(sendGSIMValue(float)), bicluster, SLOT(getGSIMValue(float)));
	//connect(setWidget, SIGNAL())

	connect(setWidget, SIGNAL(currentset(set<int>)), setViewHeader, SLOT(getCurrentSet(set<int>)));

	connect(bicluster, SIGNAL(sendMaxDegree(int)), cpWidget, SLOT(getMaxDegree(int)));
	connect(cpWidget->doubleSpinBox, SIGNAL(valueChanged(double)), bicluster, SLOT(getMinORatio(double)));
	connect(cpWidget->doubleSpinBox_2, SIGNAL(valueChanged(double)), bicluster, SLOT(getMaxORatio(double)));
	//connect(cpWidget->checkBox_2, SIGNAL(stateChanged(int)), spWidget, SLOT(setPieChartShow(int)));
	connect(cpWidget->checkBox_2, SIGNAL(stateChanged(int)), bicluster, SLOT(setSubsetsContained(int)));


	//connect(this, SIGNAL(sendDatas(vector<Volume *>&)), pcWidget, SLOT(setVolDatas(vector<Volume *>&)));
	//connect(bicluster, SIGNAL(sendFilterDatas(int*, int*, int)), pcWidget, SLOT(setFilterDatas(int*, int*, int)));
	//connect(bicluster, SIGNAL(sendClusterVoxels(vector<int>, vector<int>)), pcWidget, SLOT(setClusterVoxels(vector<int>, vector<int>)));
	//Debug 20180201 ×¢ÊÍ
	//connect(bicluster, SIGNAL(sendGlobalCluster(vector<vector<int>>, vector<vector<int>>)), /*\*/
	//	pcWidget, SLOT(setGlobalClusters(vector<vector<int>>, vector<vector<int>>)));

	//connect(bicluster, SIGNAL(sendDistanceMatrix(float*, int, vector<MaximalDimentionalSet*>)),
	//	spWidget, SLOT(getDistanceMatrix(float*, int, vector<MaximalDimentionalSet*>)));
	//connect(spWidget, SIGNAL(sendIdx(int)), bicluster, SLOT(getClusterNo(int)));
	//connect(spWidget, SIGNAL(sendGlobalSelect(int)), bicluster, SLOT(getGlobalSelect(int)));
	//connect(spWidget, SIGNAL(sendAGroup(vector<int>)), bicluster, SLOT(getAGroup(vector<int>)));
	//connect(spWidget, SIGNAL(sendGroups(vector<vector<int>>)), bicluster, SLOT(getGlobalGroups(vector<vector<int>>)));

	connect(this, SIGNAL(sendData(Volume *)), rWidget, SLOT(setData(Volume*)));
	connect(tfWidget, SIGNAL(sendTF(unsigned char*)), rWidget, SLOT(getVolumeTF(unsigned char*)));
	connect(rWidget, SIGNAL(dataLoaded(const Volume*)), tfWidget, SLOT(setVolume(const Volume*)));
	connect(bicluster, SIGNAL(clusterRegionChange()), rWidget, SLOT(regionsUpdate()));

	//connect(pcWidget, SIGNAL(volRegionChange()), rWidget, SLOT(regionsUpdate()));
	//connect(pcWidget, SIGNAL(TFIDChanged(int)), this, SLOT(getSelectedVariatesNo(int)));


	//connect(spWidget, SIGNAL(sendDistence(vector<float>)), distributionView, SLOT(getDistribution(vector<float>)));
	//connect(distributionView, SIGNAL(sendCurrentValue(float)), spWidget, SLOT(getCutValue(float)));
}