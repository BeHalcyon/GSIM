#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "ui_MainWindow.h"
#include "calEntropy.h"
#include "renderWidget.h"
#include "1dtf/TF1DWidget.h"
#include "biclusters.h"
#include "parallelCoordinate.h"
#include "ControlPanel.h"
#include "hierarchyTree.h"
#include "scatterPlot.h"
#include "donutbreakdownchart.h"
#include "setView.h"
#include "legend.h"
#include "colorbar.h"
#include "setViewHeader.h"
#include "disDistribution.h"
#include "RenderProperty.h"

class QScrollArea;
class QHBoxLayout;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void loadvolume(QStringList filenames);
signals:
	void sendDatas(vector<Volume *>& datas, QStringList names);
	void sendDatas(vector<Volume *>& datas);
	void sendData(Volume *);
	public slots:
	void getNamesofVariates();
	void getSelectedVariatesNo(int selectedNo);
	void about();
private:
	void createMenus();
	void createConnections();
private:
	vector<Volume *> vdata;
	RenderWidget *rWidget;
	TF1DWidget *tfWidget;
	Bicluster* bicluster;
	ParallelCoordinate* pcWidget;
	ControlPanel * cpWidget;
	HierarchyTree* htWidget;
	ScatterPlot* spWidget;
	DonutBreakdownChart *dbWidget;
	SetView* setWidget;
	SetViewHeader* setViewHeader;
	CalEntropy * entropyviewer;
	ColorBar* colorbar;
	Legend* legend;
	QScrollArea *scrollArea;
	DisDistribution* distributionView;
	RenderPropertyWidget* renderpropertyview;

	QMenu *fileMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;

	QAction *loadAct;
	QAction *viewAct;
	QAction *aboutAct;

	QDockWidget* dock2;
	QDockWidget* dock4;
	QDockWidget* dock5;

	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
