#include "INCLUSIONS.h"
#include "MyForm.h"

#define nbr_ptn 16


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::DataVisualization::Charting;


void Myo_app::MyForm::init_EMG_charts(void)
{
	//location of charts
	/*
	this->chart1->Location = System::Drawing::Point(336, 195);
	this->chart1->Size = System::Drawing::Size(200, 200);
	this->chart3->Location = System::Drawing::Point(336, 451);
	this->chart3->Size = System::Drawing::Size(200, 200);
	this->chart2->Location = System::Drawing::Point(623, 195);
	this->chart2->Size = System::Drawing::Size(200, 200);
	*/

	for (int i(0); i < 2; i++)
	{
		chartEMG[i]->Legends->Clear();
		chartEMG[i]->Series->Clear();
	}

	for (int i(0); i < 2; i++)
	{
		chartEMG[i]->ChartAreas->Add("area");
	}

	chart3->ChartAreas->Add("area");

	chart1->ChartAreas["area"]->AxisY->Title = L"Zero %";
	chart2->ChartAreas["area"]->AxisY->Title = L"Turn %";

	for (int i(0); i < 2; i++)
	{
		chartEMG[i]->ChartAreas["area"]->AxisX->Minimum = 0;
		chartEMG[i]->ChartAreas["area"]->AxisX->Maximum = 8;
		chartEMG[i]->ChartAreas["area"]->AxisX->Interval = 1;
		chartEMG[i]->ChartAreas["area"]->AxisY->Minimum = 0;
		chartEMG[i]->ChartAreas["area"]->AxisY->Maximum = 100;
		chartEMG[i]->ChartAreas["area"]->AxisY->Interval = 10;

		chartEMG[i]->Series->Add("radar1");
		chartEMG[i]->Series["radar1"]->ChartType = DataVisualization::Charting::SeriesChartType::Radar;
		chartEMG[i]->Series["radar1"]->BorderWidth = thickness;
		chartEMG[i]->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
		chartEMG[i]->Series["radar1"]->Color = Color::FromArgb(120, 0, 100, 255);

		chartEMG[i]->Series->Add("radar2");
		chartEMG[i]->Series["radar2"]->ChartType = DataVisualization::Charting::SeriesChartType::Radar;
		chartEMG[i]->Series["radar2"]->BorderWidth = thickness;
		chartEMG[i]->Series["radar2"]->Color = Color::FromArgb(120, 255, 0, 0);

		chartEMG[i]->ChartAreas["area"]->InnerPlotPosition->Auto = false;
		chartEMG[i]->ChartAreas["area"]->InnerPlotPosition->Height = 100;
		chartEMG[i]->ChartAreas["area"]->InnerPlotPosition->Width = 100;
		chartEMG[i]->ChartAreas["area"]->InnerPlotPosition->X = 0;
		chartEMG[i]->ChartAreas["area"]->InnerPlotPosition->Y = 0;
	}

	/// bar graph




	chart3->ChartAreas["area"]->InnerPlotPosition->Auto = false;
	chart3->ChartAreas["area"]->InnerPlotPosition->Height = 90;
	chart3->ChartAreas["area"]->InnerPlotPosition->Width = 100;
	chart3->ChartAreas["area"]->InnerPlotPosition->X = 7;
	chart3->ChartAreas["area"]->InnerPlotPosition->Y = 3;

	//	chart3->ChartAreas["area"]->AxisY->Title = L"";

	chart3->ChartAreas["area"]->AxisX->Minimum = 0;
	chart3->ChartAreas["area"]->AxisX->Maximum = 3;
	chart3->ChartAreas["area"]->AxisX->Interval = 1;
	chart3->ChartAreas["area"]->AxisY->Minimum = 0;
	chart3->ChartAreas["area"]->AxisY->Maximum = 70;
	chart3->ChartAreas["area"]->AxisY->Interval = 5;
	chart3->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::False; //db flase


	chart3->Series->Add("bar1");
	chart3->Series["bar1"]->ChartType = DataVisualization::Charting::SeriesChartType::Column;
	chart3->Series["bar1"]->BorderWidth = thickness;

	chart3->Series->Add("bar2");
	chart3->Series["bar2"]->ChartType = DataVisualization::Charting::SeriesChartType::Column;
	chart3->Series["bar2"]->BorderWidth = thickness;
	chart3->Series["bar2"]->Color = Color::FromArgb(125, 51, 255, 0);

	chart3->Series->Add("bar3");
	chart3->Series["bar3"]->ChartType = DataVisualization::Charting::SeriesChartType::Column;
	chart3->Series["bar3"]->BorderWidth = thickness;
	chart3->Series["bar3"]->Color = Color::FromArgb(125, 255, 204, 0);

	chart3->Series->Add("bar4");
	chart3->Series["bar4"]->ChartType = DataVisualization::Charting::SeriesChartType::Column;
	chart3->Series["bar4"]->BorderWidth = thickness;
	chart3->Series["bar4"]->Color = Color::FromArgb(125, 255, 0, 0);

	chart3->Legends->Add("Average MAV");
	chart3->Series["bar1"]->LegendText = "Average WAVE";
	chart3->Series["bar1"]->IsVisibleInLegend = true;

	chart3->Legends->Add("Average WAVE");
	chart3->Series["bar2"]->LegendText = "Average MAV";
	chart3->Series["bar2"]->IsVisibleInLegend = true;

	chart3->Legends->Add("Average Zero");
	chart3->Series["bar3"]->LegendText = "Average Zero";
	chart3->Series["bar3"]->IsVisibleInLegend = true;

	chart3->Legends->Add("Average Turn");
	chart3->Series["bar4"]->LegendText = "Average Turn";
	chart3->Series["bar4"]->IsVisibleInLegend = true;



	///
}

void Myo_app::MyForm::init_IMU_charts(void)
{
	//done in display_chart funcitons below
	chart6->ChartAreas->Add("area");
	chart6->ChartAreas["area"]->AxisX->Minimum = -180;
	chart6->ChartAreas["area"]->AxisX->Maximum = 180;
	chart6->ChartAreas["area"]->AxisX->Interval = 20;
	chart6->ChartAreas["area"]->AxisY->Minimum = -180;
	chart6->ChartAreas["area"]->AxisY->Maximum = 180;
	chart6->ChartAreas["area"]->AxisY->Interval = 20;
	chart6->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	chart6->Titles->Add("Orientation Myo 1 (deg)");

	chart5->ChartAreas->Add("area");
	chart5->ChartAreas["area"]->AxisX->Minimum = -180;
	chart5->ChartAreas["area"]->AxisX->Maximum = 180;
	chart5->ChartAreas["area"]->AxisX->Interval = 20;
	chart5->ChartAreas["area"]->AxisY->Minimum = -180;
	chart5->ChartAreas["area"]->AxisY->Maximum = 180;
	chart5->ChartAreas["area"]->AxisY->Interval = 20;
	chart5->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	chart5->Titles->Add("Orientation Myo 2 (deg)");

	chart7->ChartAreas->Add("area");
	chart7->ChartAreas["area"]->AxisX->Minimum = -180;
	chart7->ChartAreas["area"]->AxisX->Maximum = 180;
	chart7->ChartAreas["area"]->AxisX->Interval = 20;
	chart7->ChartAreas["area"]->AxisY->Minimum = -180;
	chart7->ChartAreas["area"]->AxisY->Maximum = 180;
	chart7->ChartAreas["area"]->AxisY->Interval = 20;
	chart7->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;

	/*
	chart7->ChartAreas->Add("area");
	chart7->ChartAreas["area"]->AxisX->Minimum = -3;
	chart7->ChartAreas["area"]->AxisX->Maximum = 3;
	chart7->ChartAreas["area"]->AxisX->Interval = 0.5;
	chart7->ChartAreas["area"]->AxisY->Minimum = -3;
	chart7->ChartAreas["area"]->AxisY->Maximum = 3;
	chart7->ChartAreas["area"]->AxisY->Interval = 0.5;
	chart7->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	chart7->Titles->Add("Accelerometer");

	chart8->ChartAreas->Add("area");
	chart8->ChartAreas["area"]->AxisX->Minimum = -400;
	chart8->ChartAreas["area"]->AxisX->Maximum = 400;
	chart8->ChartAreas["area"]->AxisX->Interval = 40;
	chart8->ChartAreas["area"]->AxisY->Minimum = -400;
	chart8->ChartAreas["area"]->AxisY->Maximum = 400;
	chart8->ChartAreas["area"]->AxisY->Interval = 40;
	chart8->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	chart8->Titles->Add("gyr");


	*/


	for (int i(0); i < 3; i++)
	{
		cc_imu[i]->ChartAreas["area"]->InnerPlotPosition->Auto = false;
		cc_imu[i]->ChartAreas["area"]->InnerPlotPosition->Height = 90;
		cc_imu[i]->ChartAreas["area"]->InnerPlotPosition->Width = 95;
		cc_imu[i]->ChartAreas["area"]->InnerPlotPosition->X = 8;
		cc_imu[i]->ChartAreas["area"]->InnerPlotPosition->Y = 5;

		cc_imu[i]->Series->Add("ori1");
		cc_imu[i]->Series["ori1"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["ori1"]->MarkerStyle = MarkerStyle::Circle;
		cc_imu[i]->Series["ori1"]->MarkerSize = 5;


		cc_imu[i]->Series->Add("acc1");
		cc_imu[i]->Series["acc1"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["acc1"]->MarkerStyle = MarkerStyle::Circle;
		cc_imu[i]->Series["acc1"]->MarkerSize = 5;

		cc_imu[i]->Series->Add("gyr1");
		cc_imu[i]->Series["gyr1"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["gyr1"]->MarkerStyle = MarkerStyle::Circle;
		cc_imu[i]->Series["gyr1"]->MarkerSize = 5;

		cc_imu[i]->Series->Add("ori2");
		cc_imu[i]->Series["ori2"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["ori2"]->MarkerStyle = MarkerStyle::Triangle;
		cc_imu[i]->Series["ori2"]->MarkerSize = 5;


		cc_imu[i]->Series->Add("acc2");
		cc_imu[i]->Series["acc2"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["acc2"]->MarkerStyle = MarkerStyle::Triangle;
		cc_imu[i]->Series["acc2"]->MarkerSize = 5;

		cc_imu[i]->Series->Add("gyr2");
		cc_imu[i]->Series["gyr2"]->ChartType = SeriesChartType::Point;
		cc_imu[i]->Series["gyr2"]->MarkerStyle = MarkerStyle::Triangle;
		cc_imu[i]->Series["gyr2"]->MarkerSize = 5;
	}



	for (int a(0); a < 3; a++) //a<3
	{
		for (int i(0); i < nbr_ptn; i++)
		{



			point_gyro_1[a, i] = (gcnew DataPoint());
			point_gyro_2[a, i] = (gcnew DataPoint());

			point_accel_1[a, i] = (gcnew DataPoint());
			point_accel_2[a, i] = (gcnew DataPoint());

			point_ori_1[a, i] = (gcnew DataPoint());
			point_ori_2[a, i] = (gcnew DataPoint());

			switch (a)
			{
			case 0:
				point_gyro_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);
				point_accel_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);
				point_ori_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);

				point_gyro_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);
				point_accel_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);
				point_ori_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 255, 0, 0);
				break;
			case 1:
				point_gyro_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);
				point_accel_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);
				point_ori_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);

				point_gyro_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);
				point_accel_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);
				point_ori_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 255, 0);
				break;
			case 2:


				point_gyro_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);
				point_accel_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);
				point_ori_1[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);

				point_gyro_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);
				point_accel_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);
				point_ori_2[a, i]->Color = Color::FromArgb(255 - (i * ((256 / nbr_ptn) - 1)), 0, 0, 255);
				break;
			}
		}
		point_gyro_1[a, 0]->MarkerSize = 10;
		point_ori_1[a, 0]->MarkerSize = 10;
		point_accel_1[a, 0]->MarkerSize = 10;

		point_gyro_2[a, 0]->MarkerSize = 10;
		point_ori_2[a, 0]->MarkerSize = 10;
		point_accel_2[a, 0]->MarkerSize = 10;
	}
	int a = 0;
}

void Myo_app::MyForm::Display_EMG(DataCollector val)
{

	for (int a(0); a < 1; a++) {
		chartEMG[a]->Series["radar1"]->Points->Clear();
		chartEMG[a]->Series["radar2"]->Points->Clear();
	}

	chart3->Series["bar1"]->Points->Clear();
	chart3->Series["bar2"]->Points->Clear();
	chart3->Series["bar3"]->Points->Clear();
	chart3->Series["bar4"]->Points->Clear();


	for (int a(0); a < 2; a++) {
		chartEMG[a]->Series["radar1"]->Points->Clear();
		chartEMG[a]->Series["radar2"]->Points->Clear();
	}

	for (int a(0); a < 8; a++) {
		for (int i(0); i < 4; i++) {

			val.FeatEMGAvg[i] = val.FeatEMGAvg[i] + (val.FeatEMG[i][a] / (float)8.0);

		}
	}

	for (int a(0); a < 8; a++)
	{

		if (!checkBox7->Checked) {
			chartEMG[0]->Series["radar1"]->Points->AddXY(a, val.FeatEMG[comboBox6->SelectedIndex][a]);
			chartEMG[0]->Series["radar2"]->Points->AddXY(a, val.FeatEMG[comboBox8->SelectedIndex][a]);
			chartEMG[1]->Series["radar1"]->Points->AddXY(a, val.FeatEMG[comboBox7->SelectedIndex][a]);
			chartEMG[1]->Series["radar2"]->Points->AddXY(a, val.FeatEMG[comboBox9->SelectedIndex][a]);
		}
		else {

			comboBox6->SelectedIndex = 0;
			comboBox8->SelectedIndex = 1;

			double normFeatAvg[4];

			for (int i = 0; i < 2; i++) {

				normFeatAvg[i] = val.FeatEMG[i][a] / val.FeatEMGAvg[i];


				if (normFeatAvg[i] > 5 && val.FeatEMGAvg[1] > deviceMyo.collector.threshold)
				{
					normFeatAvg[i] = 5;
				}
				if (normFeatAvg[i] >= 5 && val.FeatEMGAvg[1] <= deviceMyo.collector.threshold) {
					normFeatAvg[i] = 1;
				}

			}


			chartEMG[0]->Series["radar1"]->Points->AddXY(a, normFeatAvg[comboBox6->SelectedIndex]);
			chartEMG[0]->Series["radar2"]->Points->AddXY(a, normFeatAvg[comboBox8->SelectedIndex]);
			/*
			chartEMG[1]->Series["radar1"]->Points->AddXY(a, normFeatAvg[comboBox7->SelectedIndex]);
			chartEMG[1]->Series["radar2"]->Points->AddXY(a, normFeatAvg[comboBox9->SelectedIndex]);
			*/

			chartEMG[1]->Series["radar1"]->Points->AddXY(a, val.FeatEMG[comboBox7->SelectedIndex][a]);
			chartEMG[1]->Series["radar2"]->Points->AddXY(a, val.FeatEMG[comboBox9->SelectedIndex][a]);

		}



		// Average Bars
	}

	chart3->Series["bar1"]->Points->AddXY(1, val.FeatEMGAvg[0]);
	chart3->Series["bar2"]->Points->AddXY(2, val.FeatEMGAvg[1]);

	chart3->Series["bar3"]->Points->AddXY(1, val.FeatEMGAvg[2]);
	chart3->Series["bar4"]->Points->AddXY(2, val.FeatEMGAvg[3]);





}

void Myo_app::MyForm::Relabel_EMG_chart_area(Chart^ chart) {
	//updating titles, can be optimized
	if (comboBox6->SelectedIndex == 0) {
		chartEMG[0]->ChartAreas["area"]->AxisY->Title = L"WAVE";
	}
	else if (comboBox6->SelectedIndex == 1) {
		chartEMG[0]->ChartAreas["area"]->AxisY->Title = L"MAV";
	}
	else if (comboBox6->SelectedIndex == 2) {
		chartEMG[0]->ChartAreas["area"]->AxisY->Title = L"Zero %";
	}
	else if (comboBox6->SelectedIndex == 3) {
		chartEMG[0]->ChartAreas["area"]->AxisY->Title = L"Turn %";
	}



	if (comboBox8->SelectedIndex == 0) {
		chartEMG[0]->ChartAreas["area"]->AxisX->Title = L"WAVE";
	}
	else if (comboBox8->SelectedIndex == 1) {
		chartEMG[0]->ChartAreas["area"]->AxisX->Title = L"MAV";
	}
	else if (comboBox8->SelectedIndex == 2) {
		chartEMG[0]->ChartAreas["area"]->AxisX->Title = L"Zero %";
	}
	else if (comboBox8->SelectedIndex == 3) {
		chartEMG[0]->ChartAreas["area"]->AxisX->Title = L"Turn %";
	}


	//////
	if (comboBox7->SelectedIndex == 0) {
		chartEMG[1]->ChartAreas["area"]->AxisY->Title = L"WAVE";
	}
	else if (comboBox7->SelectedIndex == 1) {
		chartEMG[1]->ChartAreas["area"]->AxisY->Title = L"MAV";
	}
	else if (comboBox7->SelectedIndex == 2) {
		chartEMG[1]->ChartAreas["area"]->AxisY->Title = L"Zero %";
	}
	else if (comboBox7->SelectedIndex == 3) {
		chartEMG[1]->ChartAreas["area"]->AxisY->Title = L"Turn %";
	}

	if (comboBox9->SelectedIndex == 0) {
		chartEMG[1]->ChartAreas["area"]->AxisX->Title = L" WAVE";
	}
	else if (comboBox9->SelectedIndex == 1) {
		chartEMG[1]->ChartAreas["area"]->AxisX->Title = L" MAV";
	}
	else if (comboBox9->SelectedIndex == 2) {
		chartEMG[1]->ChartAreas["area"]->AxisX->Title = L" Zero %";
	}
	else if (comboBox9->SelectedIndex == 3) {
		chartEMG[1]->ChartAreas["area"]->AxisX->Title = L" Turn %";
	}
	//////

	if (!checkBox7->Checked) {//normalized
		chart->ChartAreas["area"]->AxisX->Minimum = 0;
		chart->ChartAreas["area"]->AxisX->Maximum = 8;
		chart->ChartAreas["area"]->AxisX->Interval = 1;
		chart->ChartAreas["area"]->AxisY->Minimum = 0;
		chart->ChartAreas["area"]->AxisY->Maximum = 100;
		chart->ChartAreas["area"]->AxisY->Interval = 10;
		chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	}
	else {
		chart->ChartAreas["area"]->AxisX->Minimum = 0;
		chart->ChartAreas["area"]->AxisX->Maximum = 8;
		chart->ChartAreas["area"]->AxisX->Interval = 1;
		chart->ChartAreas["area"]->AxisY->Minimum = 0;
		chart->ChartAreas["area"]->AxisY->Maximum = 5;
		chart->ChartAreas["area"]->AxisY->Interval = 1;
		chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	}
};

void Myo_app::MyForm::Display_ori_1(DataCollector val, Chart^ chart)
{

	chart->Series["ori1"]->Points->Clear();

	if (tabSelected != classifier) {
		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)//(nbr_ptn-1)
			{
				if (i >= val.iteration_imu) //>=
				{
					point_ori_1[a, i]->SetValueXY((double)point_ori_1[a, (i - val.iteration_imu)]->XValue, (double)point_ori_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_ori_1[a, i]->SetValueXY(val.IMUSamples[0][i][0], val.IMUSamples[1][i][0]);
						break;
					case 1:
						point_ori_1[a, i]->SetValueXY(val.IMUSamples[1][i][0], val.IMUSamples[2][i][0]);
						break;
					case 2:
						point_ori_1[a, i]->SetValueXY(val.IMUSamples[2][i][0], val.IMUSamples[0][i][0]);
						break;
					}
				}
				chart->Series["ori1"]->Points->Add(point_ori_1[a, i]);
			}
		}

	}
	else {

		float avg_IMUSamples[3] = { 0.000 };
		float sum[3] = { 0.00 };
		int samples = (int)numericUpDown6->Value;

		for (int x = 0; x < 3; x++) {

			for (int i = 0; i < samples; i++) {
				int w = (val.iteration_imu - i - 1) & 127;
				sum[x] = sum[x] + val.IMUSamples[x][w][0];
			}

			avg_IMUSamples[x] = sum[x];// / samples;

		}

		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)//(nbr_ptn-1)
			{

				if (i >= val.iteration_imu) //>=
				{
					//point_ori_1[a, i]->SetValueXY((double)point_ori_1[a, (i - val.iteration_imu)]->XValue, (double)point_ori_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_ori_1[a, i]->SetValueXY(avg_IMUSamples[0], avg_IMUSamples[1]);
						break;
					case 1:
						point_ori_1[a, i]->SetValueXY(avg_IMUSamples[1], avg_IMUSamples[2]);
						break;
					case 2:
						point_ori_1[a, i]->SetValueXY(avg_IMUSamples[2], avg_IMUSamples[0]);
						break;
					}
				}
				chart->Series["ori1"]->Points->Add(point_ori_1[a, i]);
			}
		}
	}

}

void Myo_app::MyForm::Display_ori_2(DataCollector val, Chart^ chart)
{
	chart->Series["ori2"]->Points->Clear();

	for (int a(0); a < 3; a++)
	{
		for (int i(nbr_ptn - 1); i >= 0; i--)
		{
			if (i >= val.iteration_imu)
			{
				point_ori_2[a, i]->SetValueXY((double)point_ori_2[a, (i - val.iteration_imu)]->XValue, (double)point_ori_2[a, (i - val.iteration_imu)]->YValues[0]);
			}
			else
			{
				switch (a)
				{
				case 0:
					point_ori_2[a, i]->SetValueXY(val.IMUSamples[0][i][1], val.IMUSamples[1][i][1]);
					break;
				case 1:
					point_ori_2[a, i]->SetValueXY(val.IMUSamples[1][i][1], val.IMUSamples[2][i][1]);
					break;
				case 2:
					point_ori_2[a, i]->SetValueXY(val.IMUSamples[2][i][1], val.IMUSamples[1][i][1]);
					break;
				}
			}
			chart->Series["ori2"]->Points->Add(point_ori_2[a, i]);
		}
	}

}

void Myo_app::MyForm::Display_accel_1(DataCollector val, Chart^ chart)
{
	chart->Series["acc1"]->Points->Clear();

	if (tabSelected != classifier) {

		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)
			{
				if (i >= val.iteration_imu)
				{
					point_accel_1[a, i]->SetValueXY((double)point_accel_1[a, (i - val.iteration_imu)]->XValue, (double)point_accel_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_accel_1[a, i]->SetValueXY(val.IMUSamples[3][i][0], val.IMUSamples[4][i][0]);
						break;
					case 1:
						point_accel_1[a, i]->SetValueXY(val.IMUSamples[4][i][0], val.IMUSamples[5][i][0]);
						break;
					case 2:
						point_accel_1[a, i]->SetValueXY(val.IMUSamples[5][i][0], val.IMUSamples[3][i][0]);
						break;
					}
				}
				chart->Series["acc1"]->Points->Add(point_accel_1[a, i]);
			}
		}


	}
	else {

		float avg_IMUSamples[3] = { 0.000 };
		float sum[3] = { 0.00 };
		int samples = (int)numericUpDown6->Value;

		for (int x = 0; x < 3; x++) {

			for (int i = 0; i < samples; i++) {
				sum[x] = sum[x] + val.IMUSamples[x + 3][i][0];
			}

			avg_IMUSamples[x] = sum[x] / samples;

		}


		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)
			{
				if (i >= val.iteration_imu)
				{
					point_accel_1[a, i]->SetValueXY((double)point_accel_1[a, (i - val.iteration_imu)]->XValue, (double)point_accel_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_accel_1[a, i]->SetValueXY(avg_IMUSamples[0], avg_IMUSamples[1]);
						break;
					case 1:
						point_accel_1[a, i]->SetValueXY(avg_IMUSamples[1], avg_IMUSamples[2]);
						break;
					case 2:
						point_accel_1[a, i]->SetValueXY(avg_IMUSamples[2], avg_IMUSamples[0]);
						break;
					}
				}
				chart->Series["acc1"]->Points->Add(point_accel_1[a, i]);
			}
		}



	}

}

void Myo_app::MyForm::Display_accel_2(DataCollector val, Chart^ chart)
{
	chart->Series["acc2"]->Points->Clear();
	for (int a(0); a < 3; a++)
	{
		for (int i(nbr_ptn - 1); i >= 0; i--)
		{
			if (i >= val.iteration_imu)
			{
				point_accel_2[a, i]->SetValueXY((double)point_accel_2[a, (i - val.iteration_imu)]->XValue, (double)point_accel_2[a, (i - val.iteration_imu)]->YValues[0]);
			}
			else
			{
				switch (a)
				{
				case 0:
					point_accel_2[a, i]->SetValueXY(val.IMUSamples[3][i][1], val.IMUSamples[4][i][1]);
					break;
				case 1:
					point_accel_2[a, i]->SetValueXY(val.IMUSamples[4][i][1], val.IMUSamples[5][i][1]);
					break;
				case 2:
					point_accel_2[a, i]->SetValueXY(val.IMUSamples[5][i][1], val.IMUSamples[3][i][1]);
					break;
				}
			}
			chart->Series["acc2"]->Points->Add(point_accel_2[a, i]);
		}
	}
}

void Myo_app::MyForm::Display_gyro_1(DataCollector val, Chart^ chart)
{
	chart->Series["gyr1"]->Points->Clear();

	if (tabSelected != classifier) {
		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)//(nbr_ptn-1)
			{
				if (i >= val.iteration_imu) //>=
				{
					point_gyro_1[a, i]->SetValueXY((double)point_gyro_1[a, (i - val.iteration_imu)]->XValue, (double)point_gyro_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_gyro_1[a, i]->SetValueXY(val.IMUSamples[6][i][0], val.IMUSamples[7][i][0]);
						break;
					case 1:
						point_gyro_1[a, i]->SetValueXY(val.IMUSamples[7][i][0], val.IMUSamples[8][i][0]);
						break;
					case 2:
						point_gyro_1[a, i]->SetValueXY(val.IMUSamples[8][i][0], val.IMUSamples[6][i][0]);
						break;
					}
				}
				chart->Series["gyr1"]->Points->Add(point_gyro_1[a, i]);
			}
		}

	}
	else {

		float avg_IMUSamples[3] = { 0.000 };
		float sum[3] = { 0.00 };
		int samples = (int)numericUpDown6->Value;

		for (int x = 0; x < 3; x++) {

			for (int i = 0; i < samples; i++) {
				sum[x] = sum[x] + val.IMUSamples[x + 6][i][0];
			}

			avg_IMUSamples[x] = sum[x] / samples;

		}

		for (int a(0); a < 3; a++)
		{
			for (int i(nbr_ptn - 1); i >= 0; i--)//(nbr_ptn-1)
			{

				if (i >= val.iteration_imu) //>=
				{
					point_gyro_1[a, i]->SetValueXY((double)point_gyro_1[a, (i - val.iteration_imu)]->XValue, (double)point_gyro_1[a, (i - val.iteration_imu)]->YValues[0]);
				}
				else
				{
					switch (a)
					{
					case 0:
						point_gyro_1[a, i]->SetValueXY(avg_IMUSamples[0], avg_IMUSamples[1]);
						break;
					case 1:
						point_gyro_1[a, i]->SetValueXY(avg_IMUSamples[1], avg_IMUSamples[2]);
						break;
					case 2:
						point_gyro_1[a, i]->SetValueXY(avg_IMUSamples[2], avg_IMUSamples[0]);
						break;
					}
				}
				chart->Series["gyr1"]->Points->Add(point_gyro_1[a, i]);
			}
		}
	}

}

void Myo_app::MyForm::Display_gyro_2(DataCollector val, Chart^ chart)
{
	chart->Series["gyr2"]->Points->Clear(); //db
	for (int a(0); a < 3; a++)
	{
		for (int i(nbr_ptn - 1); i >= 0; i--)
		{
			if (i >= val.iteration_imu)
				point_gyro_2[a, i]->SetValueXY((double)point_gyro_2[a, (i - val.iteration_imu)]->XValue, (double)point_gyro_2[a, (i - val.iteration_imu)]->YValues[0]);
			else
			{
				switch (a)
				{
				case 0:
					point_gyro_2[a, i]->SetValueXY(val.IMUSamples[6][i][1], val.IMUSamples[7][i][1]);
					break;
				case 1:
					point_gyro_2[a, i]->SetValueXY(val.IMUSamples[7][i][1], val.IMUSamples[8][i][1]);
					break;
				case 2:
					point_gyro_2[a, i]->SetValueXY(val.IMUSamples[8][i][1], val.IMUSamples[6][i][1]);
					break;
				}
			}
			chart->Series["gyr2"]->Points->Add(point_gyro_2[a, i]);
		}
	}

}

void Myo_app::MyForm::Display_IMU_chart_area(ComboBox^ cbox, Chart^chart) {

	/*

	if (cbox == comboBox4){
	switch (selectedChart_Cbox4) {
	case 0:
	Display_ori_1(test20.collector2, chart);
	break;
	case 1:
	Display_gyro_1(test20.collector2, chart);
	break;
	case 2:
	Display_accel_1(test20.collector2, chart);
	break;
	case 3:
	Display_ori_2(test20.collector2, chart);
	break;
	case 4:
	Display_gyro_2(test20.collector2, chart);
	break;
	case 5:
	Display_accel_2(test20.collector2, chart);
	break;
	}

	}


	*/
	//if (cbox == comboBox5){ db db db db db
	switch (selectedChart_Cbox5) {
	case 0:
		Display_ori_1(deviceMyo.collector, chart);
		break;
	case 1:
		Display_gyro_1(deviceMyo.collector, chart);
		break;
	case 2:
		Display_accel_1(deviceMyo.collector, chart);
		break;
	case 3:
		Display_ori_2(deviceMyo.collector, chart);
		break;
	case 4:
		Display_gyro_2(deviceMyo.collector, chart);
		break;
	case 5:
		Display_accel_2(deviceMyo.collector, chart);
		break;
	}
	//}

}

void Myo_app::MyForm::Display_IMU_CB4(Chart^ chart) {
	switch (selectedChart_Cbox4) {
	case 0:
		Display_ori_1(deviceMyo.collector, chart);
		break;
	case 1:
		Display_gyro_1(deviceMyo.collector, chart);
		break;
	case 2:
		Display_accel_1(deviceMyo.collector, chart);
		break;
	case 3:
		Display_ori_2(deviceMyo.collector, chart);
		break;
	case 4:
		Display_gyro_2(deviceMyo.collector, chart);
		break;
	case 5:
		Display_accel_2(deviceMyo.collector, chart);
		break;
	}
}

void Myo_app::MyForm::Relabel_IMU_chart_area(ComboBox^ cbox, Chart^ chart) {

	chart->Series["ori1"]->Points->Clear();
	chart->Series["ori2"]->Points->Clear();
	chart->Series["gyr1"]->Points->Clear();
	chart->Series["gyr2"]->Points->Clear();
	chart->Series["acc1"]->Points->Clear();
	chart->Series["acc2"]->Points->Clear();


	if (cbox == comboBox4) {
		switch (selectedChart_Cbox4)
		{
		case 0: //Ori1
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 1 (deg)");

			label23->Text = "Roll";
			label28->Text = "Yaw";
			label55->Text = "Pitch";

			label59->Text = "Roll";
			label60->Text = "Pitch";
			label61->Text = "Yaw";



			break;
		case 1: //Gyro1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 1 (deg/s)");

			label23->Text = "X";
			label28->Text = "Z";
			label55->Text = "Y";

			label59->Text = "X";
			label60->Text = "Y";
			label61->Text = "Z";

			break;
		case 2: //Accel1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 1 (g's)");

			label23->Text = "X";
			label28->Text = "Z";
			label55->Text = "Y";

			label59->Text = "X";
			label60->Text = "Y";
			label61->Text = "Z";

			break;
		case 3: //Ori2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 2 (deg)");

			label23->Text = "Roll";
			label28->Text = "Yaw";
			label55->Text = "Pitch";

			label59->Text = "Roll";
			label60->Text = "Pitch";
			label61->Text = "Yaw";

			break;
		case 4: //Gyr2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 2 (deg/s)");

			label23->Text = "X";
			label28->Text = "Z";
			label55->Text = "Y";

			label59->Text = "X";
			label60->Text = "Y";
			label61->Text = "Z";
			break;
		case 5:	//Accel2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 2 (g's)");

			label23->Text = "X";
			label28->Text = "Z";
			label55->Text = "Y";

			label59->Text = "X";
			label60->Text = "Y";
			label61->Text = "Z";
			break;

		}
	}
	else if (cbox == comboBox5) {
		switch (selectedChart_Cbox5)
		{
		case 0: //Ori1
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 1 (deg)");

			label56->Text = "Roll";
			label57->Text = "Yaw";
			label58->Text = "Pitch";

			label62->Text = "Roll";
			label63->Text = "Pitch";
			label64->Text = "Yaw";



			break;
		case 1: //Gyro1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 1 (deg/s)");

			label56->Text = "X";
			label57->Text = "Z";
			label58->Text = "Y";

			label62->Text = "X";
			label63->Text = "Y";
			label64->Text = "Z";

			break;
		case 2: //Accel1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 1 (g's)");

			label56->Text = "X";
			label57->Text = "Z";
			label58->Text = "Y";

			label62->Text = "X";
			label63->Text = "Y";
			label64->Text = "Z";


			break;
		case 3: //Ori2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 2 (deg)");
			label56->Text = "Roll";
			label57->Text = "Yaw";
			label58->Text = "Pitch";

			label62->Text = "Roll";
			label63->Text = "Pitch";
			label64->Text = "Yaw";
			break;
		case 4: //Gyr2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 2 (deg/s)");

			label56->Text = "X";
			label57->Text = "Z";
			label58->Text = "Y";

			label62->Text = "X";
			label63->Text = "Y";
			label64->Text = "Z";

			break;
		case 5:	//Accel2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 2 (g's)");

			label56->Text = "X";
			label57->Text = "Z";
			label58->Text = "Y";

			label62->Text = "X";
			label63->Text = "Y";
			label64->Text = "Z";

			break;

		}
	}
	else if (cbox == comboBox11) {
		switch (selectedChart_Cbox11)
		{
		case 0: //Ori1
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 1 (deg)");


			break;
		case 1: //Gyro1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 1 (deg/s)");


			break;
		case 2: //Accel1

			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 1 (g's)");



			break;
		case 3: //Ori2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -180;
			chart->ChartAreas["area"]->AxisX->Maximum = 180;
			chart->ChartAreas["area"]->AxisX->Interval = 20;
			chart->ChartAreas["area"]->AxisY->Minimum = -180;
			chart->ChartAreas["area"]->AxisY->Maximum = 180;
			chart->ChartAreas["area"]->AxisY->Interval = 20;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Orientation Myo 2 (deg)");

			break;
		case 4: //Gyr2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -400;
			chart->ChartAreas["area"]->AxisX->Maximum = 400;
			chart->ChartAreas["area"]->AxisX->Interval = 40;
			chart->ChartAreas["area"]->AxisY->Minimum = -400;
			chart->ChartAreas["area"]->AxisY->Maximum = 400;
			chart->ChartAreas["area"]->AxisY->Interval = 40;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Gyrometer Myo 2 (deg/s)");



			break;
		case 5:	//Accel2
			chart->ChartAreas->Clear();
			chart->ChartAreas->Add("area");
			chart->ChartAreas["area"]->AxisX->Minimum = -3;
			chart->ChartAreas["area"]->AxisX->Maximum = 3;
			chart->ChartAreas["area"]->AxisX->Interval = 0.5;
			chart->ChartAreas["area"]->AxisY->Minimum = -3;
			chart->ChartAreas["area"]->AxisY->Maximum = 3;
			chart->ChartAreas["area"]->AxisY->Interval = 0.5;
			chart->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
			chart->Titles->Clear();
			chart->Titles->Add("Accelerometer Myo 2 (g's)");


			break;

		}
	}

}

void Myo_app::MyForm::playbackEMG(std::ifstream& file) {
	std::string emgLine;
	std::string emgTemp;

	for (int samp = 0; samp < 4; samp++) {
		std::getline(file, emgLine);

		if (!file.good()) {

			if (checkBox6->Checked == true) {
				file.close();
				file.open(stdOpenEMGFile);
				std::getline(file, emgTemp);
			}
			else {
				//stop upon loop ending
				// db
				openEMGFile.close();
				//
				break;
			}

		}
		if (playbackLoop) {
			currentNumberLinesEmgPlayback++;
		}
		textBox1->Text = "" + currentNumberLinesEmgPlayback; //db
		std::stringstream emgIss(emgLine);

		for (int col = 0; col < 9; col++) {
			std::string emgVal;
			std::getline(emgIss, emgVal, ',');

			if (!emgIss.good()) {
				//break;
			}

			std::stringstream converter(emgVal);

			if (col != 0) {
				converter >> deviceMyo.collector.emgSamples[col - 1][deviceMyo.collector.iteration_emg][0];
			}

		}

		deviceMyo.collector.iteration_emg++;
		deviceMyo.collector.iteration_emg &= 127;


	}
}

void Myo_app::MyForm::playbackIMU(std::ifstream& file) {

	for (int samp = 0; samp < 1; samp++) { // #RF : one iteration for loop used for breaking out of main timer loop to stop automatic looping if loop flag is not checked, 

		std::string imuLine;
		std::string imuTemp;

		std::getline(file, imuLine);

		// not exactly sure what this if statement is doing
		if (!file.good()) {
			//if loop box checked, loop, else stop loop
			if (checkBox6->Checked == true) {
				file.close();
				file.open(stdOpenIMUFile);
				std::getline(file, imuTemp);
			}
			else {
				//stop upon loop ending db
				openIMUFile.close();

				break;
			}
		}

		++currentNumberLinesImuPlayback;

		std::stringstream imuIss(imuLine);

		for (int col = 0; col < 10; col++) {

			std::string imuVal;
			std::getline(imuIss, imuVal, ',');
			if (!imuIss.good()) {
				//break;
			}
			std::stringstream converter(imuVal);
			if (col != 0) {
				converter >> deviceMyo.collector.IMUSamples[col - 1][deviceMyo.collector.iteration_imu][0];
			}

		}

		for (int col = 0; col < 9; col++) {
			std::string imuVal;
			std::getline(imuIss, imuVal, ',');
			if (!imuIss.good()) {
				//break;
			}
			std::stringstream converter(imuVal);

			converter >> deviceMyo.collector.IMUSamples[col][deviceMyo.collector.iteration_imu][1];

		}

	}

}

// mmav
void Myo_app::MyForm::mmav_display_line(DataCollector val)
{

	mmav_increment_axis();

	deviceMyo.collector.threshold_mmav = (int)numericUpDown1->Value;

	chart4->Series["threshold"]->Points->Clear();

	for (int i(0); i < chart4->ChartAreas["area"]->AxisX->Maximum; i++) {

		chart4->Series["threshold"]->Points->AddXY(i, deviceMyo.collector.threshold_mmav);

	}

	float  sum = 0;

		for (int a(0); a < 8; a++)
		{

			//	chart4->Series["sensor" + a + ""]->Points->AddXY(ite, val.FeatV[1][a]);

			sum = sum + val.FeatEMG[1][a];

			clear_state_feature[a] = false;

			if (clear_state_feature[a] == false)
			{
				for (int i(0); i < 4; i++)
					chart4->Series["sensor" + a + ""]->Points->Clear();
				clear_state_feature[a] = true;
			}
		}

		deviceMyo.collector.avg_mav = sum / (float)8.00;

		chart4->Series["mmav"]->Points->AddXY(ite, deviceMyo.collector.avg_mav);
	
}

// mmav increment graph
void Myo_app::MyForm::mmav_increment_axis(void)
{
	ite++;

	if (ite > xmax)
	{
		xmin = xmin + 1;
		xmax = xmax + 1;
		//for (int i(0); i < 4; i++)
		//{
		chart4->ChartAreas["area"]->AxisX->Minimum = xmin;
		chart4->ChartAreas["area"]->AxisX->Maximum = xmax;
		//}
	}
}

void Myo_app::MyForm::init_mmav_chart(void)
{
	chart4->ChartAreas->Add("area");
	chart4->ChartAreas["area"]->AxisX->Minimum = 0;
	chart4->ChartAreas["area"]->AxisX->Maximum = 1000;
	chart4->ChartAreas["area"]->AxisX->Interval = 1;
	chart4->ChartAreas["area"]->AxisY->Minimum = 0;
	chart4->ChartAreas["area"]->AxisY->Maximum = 100;
	chart4->ChartAreas["area"]->AxisY->Interval = 10;
	chart4->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::False;
	chart4->ChartAreas["area"]->AxisY->Title = L"EMG sensors";

	chart4->ChartAreas["area"]->InnerPlotPosition->Auto = false;
	chart4->ChartAreas["area"]->InnerPlotPosition->Height = 100;
	chart4->ChartAreas["area"]->InnerPlotPosition->Width = 100;
	chart4->ChartAreas["area"]->InnerPlotPosition->X = 4;
	chart4->ChartAreas["area"]->InnerPlotPosition->Y = 2;

	for (int a(0); a < 8; a++)
	{
		chart4->Series->Add("sensor" + a + "");
		chart4->Series["sensor" + a + ""]->ChartType = DataVisualization::Charting::SeriesChartType::FastLine;
		chart4->Series["sensor" + a + ""]->BorderWidth = thickness;
	}

	chart4->Series->Add("threshold");
	chart4->Series["threshold"]->ChartType = DataVisualization::Charting::SeriesChartType::FastLine;
	chart4->Series["threshold"]->BorderWidth = 2;
	chart4->Series["threshold"]->Color = Color::HotPink;

	chart4->Series->Add("mmav");
	chart4->Series["mmav"]->ChartType = DataVisualization::Charting::SeriesChartType::FastLine;
	chart4->Series["mmav"]->BorderWidth = 5;
	chart4->Series["mmav"]->Color = Color::Black;

	chart4->Series["sensor0"]->Color = Color::Green;
	chart4->Series["sensor1"]->Color = Color::Red;
	chart4->Series["sensor2"]->Color = Color::Blue;
	chart4->Series["sensor3"]->Color = Color::DarkViolet;
	chart4->Series["sensor4"]->Color = Color::DarkSlateGray;
	chart4->Series["sensor5"]->Color = Color::DarkOrange;
	chart4->Series["sensor6"]->Color = Color::DarkCyan;
	chart4->Series["sensor7"]->Color = Color::Black;
}

void Myo_app::MyForm::recordData(int it_emg_view, int it_imu_view) {
	//four iterations for four samples of EMG to one IMU
	for (int i = 0; i < 4; i++)
	{
		int it_emg_write = (it_emg_view - 3 + i) & 127;
		//for (int lineIndex = 0; lineIndex < 128; lineIndex++){// line1 interation loops
		//recording EMG and IMU
		for (int columnIndex = 0; columnIndex < 8; columnIndex++) {

			if (checkBox8->Checked) {
				fileEMGRecord << deviceMyo.collector.emgSamples[columnIndex][it_emg_write][0] << ", ";
			}
			else {
				fileEMGRecord << ", ";
			}
		}
		fileEMGRecord << "\n";

		if (checkBox8->Checked) {
			if (placeMarkerEMG && i == 0) {
				fileEMGRecord << "x, ";
				placeMarkerEMG = false;
			}
			else {
				fileEMGRecord << " ,";
			}
		}
	}


	if (twoMyos) {

		for (int columnIndex = 0; columnIndex < 9; columnIndex++) {

			if (checkBox9->Checked) {
				fileIMURecord << deviceMyo.collector.IMUSamples[columnIndex][it_imu_view][0] << ", ";
			}

		}

		for (int columnIndex = 0; columnIndex < 9; columnIndex++) {

			if (checkBox9->Checked) {
				fileIMURecord << deviceMyo.collector.IMUSamples[columnIndex][it_imu_view][1] << ", ";
			}

		}

		fileIMURecord << "\n";

	}
	else {

		for (int columnIndex = 0; columnIndex < 9; columnIndex++) {

			if (checkBox9->Checked) {
				fileIMURecord << deviceMyo.collector.IMUSamples[columnIndex][it_imu_view][0] << ",";
			}

		}

		fileIMURecord << "\n";

	}

	if (checkBox9->Checked) {
		if (placeMarkerIMU) {

			fileIMURecord << "x, ";
			placeMarkerIMU = false;
		}
		else {
			fileIMURecord << " ,";
		}
	}

}

void Myo_app::MyForm::printEMG(int it_emg_view) {
	textBox54->Text = "" + deviceMyo.collector.emgSamples[0][it_emg_view][0];
	textBox51->Text = "" + deviceMyo.collector.emgSamples[1][it_emg_view][0];
	textBox52->Text = "" + deviceMyo.collector.emgSamples[2][it_emg_view][0];
	textBox49->Text = "" + deviceMyo.collector.emgSamples[3][it_emg_view][0];
	textBox53->Text = "" + deviceMyo.collector.emgSamples[4][it_emg_view][0];
	textBox15->Text = "" + deviceMyo.collector.emgSamples[5][it_emg_view][0];
	textBox50->Text = "" + deviceMyo.collector.emgSamples[6][it_emg_view][0];
	textBox48->Text = "" + deviceMyo.collector.emgSamples[7][it_emg_view][0];
}

void Myo_app::MyForm::printIMU(int it_imu_view) {
	//Myo 1
	//ori
	textBox2->Text = "" + deviceMyo.collector.IMUSamples[0][it_imu_view][0];
	textBox3->Text = "" + deviceMyo.collector.IMUSamples[1][it_imu_view][0];
	textBox4->Text = "" + deviceMyo.collector.IMUSamples[2][it_imu_view][0];
	//accel
	textBox5->Text = "" + deviceMyo.collector.IMUSamples[3][it_imu_view][0];
	textBox6->Text = "" + deviceMyo.collector.IMUSamples[4][it_imu_view][0];
	textBox7->Text = "" + deviceMyo.collector.IMUSamples[5][it_imu_view][0];
	//gyro
	textBox12->Text = "" + deviceMyo.collector.IMUSamples[6][it_imu_view][0];
	textBox13->Text = "" + deviceMyo.collector.IMUSamples[7][it_imu_view][0];
	textBox11->Text = "" + deviceMyo.collector.IMUSamples[8][it_imu_view][0];

	//Myo 2
	//ori
	textBox23->Text = "" + deviceMyo.collector.IMUSamples[0][it_imu_view][1];
	textBox21->Text = "" + deviceMyo.collector.IMUSamples[1][it_imu_view][1];
	textBox17->Text = "" + deviceMyo.collector.IMUSamples[2][it_imu_view][1];
	//accel
	textBox28->Text = "" + deviceMyo.collector.IMUSamples[3][it_imu_view][1];
	textBox32->Text = "" + deviceMyo.collector.IMUSamples[4][it_imu_view][1];
	textBox27->Text = "" + deviceMyo.collector.IMUSamples[5][it_imu_view][1];
	//gyro
	textBox24->Text = "" + deviceMyo.collector.IMUSamples[6][it_imu_view][1];
	textBox25->Text = "" + deviceMyo.collector.IMUSamples[7][it_imu_view][1];
	textBox26->Text = "" + deviceMyo.collector.IMUSamples[8][it_imu_view][1];
}

void Myo_app::MyForm::updateStatus() {
	if (myoStreaming) {
		textBox33->Text = "Myo";
	}
	else if (playbackLoop) {
		textBox33->Text = "Text File";
	}
	else {
		textBox33->Text = "No Data Source";
	}

	// status
	if (endtimer1) {
		textBox34->Text = "Paused";
	}
	else if (!endtimer1 && myoStreaming) {
		textBox34->Text = "Streaming";
	}
	else if (checkBox6->Checked && playbackLoop) {
		textBox34->Text = "Looping";
	}
	else if (playbackLoop && !checkBox6->Checked) {
		textBox34->Text = "Playing";
	}

	// error
	if (playbackLoop && myoStreaming) {
		textBox33->Text = "ERROR";
	}
	progressBar2->Value = deviceMyo.collector.battery1;
	progressBar3->Value = deviceMyo.collector.battery2;
}

void Myo_app::MyForm::display_IMU_CB11_CH7() {
	switch (selectedChart_Cbox11) {
	case 0:
		Display_ori_1(deviceMyo.collector, chart7);
		break;
	case 1:
		Display_gyro_1(deviceMyo.collector, chart7);
		break;
	case 2:
		Display_accel_1(deviceMyo.collector, chart7);
		break;
	case 3:
		Display_ori_2(deviceMyo.collector, chart7);
		break;
	case 4:
		Display_gyro_2(deviceMyo.collector, chart7);
		break;
	case 5:
		Display_accel_2(deviceMyo.collector, chart7);
		break;
	}
}

void Myo_app::MyForm::svm_create_model() {

	//creates file with all training data

	//default model for prediction realtime
	model_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + ".txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(model_name);
	ofile1.open(stdRecordLDAFileName);

	// model A for testing accuracy
	model_A_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + "_A.txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(model_A_name);
	ofile2.open(stdRecordLDAFileName);

	// model B for testing accuracy
	model_B_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + "_B.txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(model_B_name);
	ofile3.open(stdRecordLDAFileName);

	for (int i = 0; i < deviceMyo.collector.currentTotalClasses; i++)
	{

		// main model for real-time prediction
		for (int k = 0; k < (deviceMyo.collector.numWC[i]); k++) {

			ofile1 << i << " ";

			for (int j = 0; j < (maxFeatures); j++) {

				ofile1 << j << ":" << deviceMyo.collector.classifierTrainer[i][k][j] << " ";
			}


			ofile1 << "\n";


		}

		// model A for testing accuracy gets first half of the training data
		for (int k = 0; k < (deviceMyo.collector.numWC[i] / 2); k++) {

			ofile2 << i << " ";

			for (int j = 0; j < (maxFeatures); j++) {

				ofile2 << j << ":" << deviceMyo.collector.classifierTrainer[i][k][j] << " ";
			}


			ofile2 << "\n";


		}

		// model B for testing accuracy gets second half of the training data
		for (int k = (deviceMyo.collector.numWC[i] / 2); k < (deviceMyo.collector.numWC[i]); k++) {

			ofile3 << i << " ";

			for (int j = 0; j < (maxFeatures); j++) {

				ofile3 << j << ":" << deviceMyo.collector.classifierTrainer[i][k][j] << " ";
			}


			ofile3 << "\n";


		}

	}

	ofile1.close();
	ofile2.close();
	ofile3.close();


	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	//creats a model from training data file
	//String^ systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -t "+ svm_kernel_type + " " + LDARecordDirectory + "\\" + textBox36->Text + ".txt";
	String^ systeminput2;
	String^ systeminputA;
	String^ systeminputB;

	if (comboBox12->SelectedIndex <= 4) {
		// main model
		systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -t " + svm_kernel_type + " "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt";

		// model A
		systeminputA = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -t " + svm_kernel_type + " "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_A.txt";

		// model B
		systeminputB = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -t " + svm_kernel_type + " "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_B.txt";
	}
	else if (comboBox12->SelectedIndex > 4 && comboBox12->SelectedIndex <= 8) {

		// main model
		systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -s 1 -t " + (svm_kernel_type)+" "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt";

		// model A
		systeminputA = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -s 1 -t " + (svm_kernel_type)+" "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_A.txt";

		// model B
		systeminputB = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -q -s 1 -t " + (svm_kernel_type)+" "
			+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_B.txt";
	}

	~svm_kernel_type;

	// creates main model
	std::string systeminput = context.marshal_as<std::string>(systeminput2);
	const char* systeminput3 = systeminput.c_str();
	char* systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);
	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL,
		&si,
		&pi
		);

	// creates model A
	systeminput = context.marshal_as<std::string>(systeminputA);
	systeminput3 = systeminput.c_str();
	systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);
	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL,
		&si,
		&pi
		);

	// creates model B
	systeminput = context.marshal_as<std::string>(systeminputB);
	systeminput3 = systeminput.c_str();
	systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);
	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL,
		&si,
		&pi
		);

	//save names of gestures

	model_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + ".labels.txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(model_name);
	fileLDARecord.open(stdRecordLDAFileName);

	for (int i = 0; i < deviceMyo.collector.currentTotalClasses; i++)
	{

		fileLDARecord << gestureNames[i] << " " << pictures[i] << "\n";
	}

	fileLDARecord.close();
	//


	//saveLDA = false;


}

// using C-svc
void Myo_app::MyForm::svm_predict() {
	//prediction
	//creating current feature input file to fead the predictor

	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\input.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	fileLDAPredictInput.open(stdLDAPredictInputFileName);

	fileLDAPredictInput << "5 ";
	int currentFeatNum = 0;
	num_features_used = 4;

	for (int i = 0; i < FtNm; i++) {

		if ((i == 0 && checkBox1->Checked) || (i == 1 && checkBox2->Checked) || (i == 2 && checkBox3->Checked) || (i == 3 && checkBox4->Checked)) {

			for (int j = 0; j < numSensors; j++) {

				if ((i == 0 && checkBox1->Checked) || (i == 1 && checkBox2->Checked) || (i == 2 && checkBox3->Checked) || (i == 3 && checkBox4->Checked)) {

					fileLDAPredictInput << currentFeatNum << ":" << deviceMyo.collector.FeatEMG[i][j] << " ";

				}


				currentFeatNum++;
				// Sensor1FeaT1, Sens2Feat1, SEns3Feat1, ... // Sensor1Feat2, Sens2Feat2..etc
			}

		}
		else {
			fileLDAPredictInput << currentFeatNum << ":" << 0 << " ";
			num_features_used--;
			currentFeatNum++;
		}


	}
	fileLDAPredictInput.close();

	// creates output file and reads to textBox


	// command prompt command to predit and save output file with gesture prediction

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// String^ LDAPredictInput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe -q -s 1"
	// -s 1 <- potentially more accurate
	// -s 0

	String^ LDAPredictInput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe -q " + folderBrowserDialog2->SelectedPath + "\\input.txt "
		+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt.model "
		+ folderBrowserDialog2->SelectedPath + "\\output.txt";

	std::string LDAPredictInput = context.marshal_as<std::string>(LDAPredictInput2);
	const char* LDAPredictInput3 = LDAPredictInput.c_str();
	char* LDAPredictInputFinal = new char[LDAPredictInput.length() + 1];
	strcpy(LDAPredictInputFinal, LDAPredictInput3);
	CreateProcess(
		NULL,
		LDAPredictInputFinal,
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL,
		&si,
		&pi
		);


	// open the output file and read it to the GUI

	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\output.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	openLDAPredictionOutput.open(stdLDAPredictInputFileName);


	int x = 10;
	while (openLDAPredictionOutput >> x);

	openLDAPredictionOutput.close();

	//label79->Text = "" + x;

	//std::string output2;
	//output2 << fileLDAPredictInput;
	//std::getline(openLDAPredictionOutput, output2);
	String^ DispString = gcnew String(gestureNames[x].c_str());
	textBox37->Text = DispString;

	if (pictures[x] != "0" && pictures[x] != "") {
		String^ PictureDirectory_system = gcnew String(pictures[x].c_str());
		pictureBox1->Load(PictureDirectory_system);
	}

}

// using nu-svc
void Myo_app::MyForm::svm_predict_2()
{
	//prediction
	//creating current feature input file to fead the predictor


	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\input.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	fileLDAPredictInput.open(stdLDAPredictInputFileName);

	fileLDAPredictInput << "5 ";
	int currentFeatNum = 0;
	num_features_used = 4;

	for (int i = 0; i < FtNm; i++) {

		if ((i == 0 && checkBox1->Checked) || (i == 1 && checkBox2->Checked) || (i == 2 && checkBox3->Checked) || (i == 3 && checkBox4->Checked)) {

			for (int j = 0; j < numSensors; j++) {

				if ((i == 0 && checkBox1->Checked) || (i == 1 && checkBox2->Checked) || (i == 2 && checkBox3->Checked) || (i == 3 && checkBox4->Checked)) {

					fileLDAPredictInput << currentFeatNum << ":" << deviceMyo.collector.FeatEMG[i][j] << " ";

				}

				currentFeatNum++;
				// Sensor1FeaT1, Sens2Feat1, SEns3Feat1, ... // Sensor1Feat2, Sens2Feat2..etc
			}

		}
		else {
			fileLDAPredictInput << currentFeatNum << ":" << 0 << " ";
			num_features_used--;
			currentFeatNum++;
		}

	}
	fileLDAPredictInput.close();

	// creates output file and reads to textBox


	// command prompt command to predit and save output file with gesture prediction

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// String^ LDAPredictInput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe -q -s 1"
	// -s 1 <- potentially more accurate
	// -s 0

	String^ LDAPredictInput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe -q " + folderBrowserDialog2->SelectedPath + "\\input.txt "
		+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt.model "
		+ folderBrowserDialog2->SelectedPath + "\\output.txt";

	std::string LDAPredictInput = context.marshal_as<std::string>(LDAPredictInput2);
	const char* LDAPredictInput3 = LDAPredictInput.c_str();
	char* LDAPredictInputFinal = new char[LDAPredictInput.length() + 1];
	strcpy(LDAPredictInputFinal, LDAPredictInput3);
	CreateProcess(
		NULL,
		LDAPredictInputFinal,
		NULL, NULL, FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL,
		&si,
		&pi
		);


	// open the output file and read it to the GUI

	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\output.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	openLDAPredictionOutput.open(stdLDAPredictInputFileName);


	int x = 10;
	while (openLDAPredictionOutput >> x);

	openLDAPredictionOutput.close();

//	label79->Text = "" + x;

	//std::string output2;
	//output2 << fileLDAPredictInput;
	//std::getline(openLDAPredictionOutput, output2);
	String^ DispString = gcnew String(gestureNames[x].c_str());
	textBox37->Text = DispString;

	if (pictures[x] != "0" && pictures[x] != "") {
		String^ PictureDirectory_system = gcnew String(pictures[x].c_str());
		pictureBox1->Load(PictureDirectory_system);
		pictureBox1->AutoSize = true;
	}






}

//becca functions
void Myo_app::MyForm::lda_classify_train()
{
	/*
	insert becca's code here

	format:

	comment
	syntax
	max index

	access the training data in the array:
	test20.collector2.LDATrainer[maxClasses][maxWindowNumber][maxFeatures]
	LDATrainer[30][1024][64]

	access number of samples per class in training array:
	test20.collector2.numWC[test20.collector2.currentTotalClasses]
	numWC[currentTotalClasses] - changes depending how mnay gestures you add

	access current live data in array:
	test20.collector2.FeatEMG[FtNm][numSensors]
	FeatEMG[4][8]

	*/

	// save gesture names
}

void Myo_app::MyForm::lda_classify_predict() {
	// becca lda predict function

	float FeatureVectorLive[maxFeatures];

	//creating current feature input file to fead the predictor
	//LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\input.txt";
	//stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	//fileLDAPredictInput.open(stdLDAPredictInputFileName);

	int currentFeatNum = 0;

	for (int i = 0; i < FtNm; i++) {

		for (int j = 0; j < numSensors; j++) {

			FeatureVectorLive[currentFeatNum] = deviceMyo.collector.FeatEMG[i][j];

			currentFeatNum++;
			// Sensor1FeaT1, Sens2Feat1, SEns3Feat1, ... // Sensor1Feat2, Sens2Feat2..etc
		}

	}

	int x = 0;

	x = lda.predict(FeatureVectorLive);
	String^ DispString = gcnew String(gestureNames[x].c_str());
	textBox37->Text = DispString;


}

void Myo_app::MyForm::classifier_training() {

	if (deviceMyo.collector.avg_mav >= (float)deviceMyo.collector.threshold_mmav) {

		// check if window_index has reached max
		deviceMyo.collector.feature_index = 0;

		for (int i = 0; i < FtNm; i++) {

			if ((i == 0 && checkBox1->Checked) || (i == 1 && checkBox2->Checked) || (i == 2 && checkBox3->Checked) || (i == 3 && checkBox4->Checked)) {

				for (int j = 0; j < numSensors; j++) {

					deviceMyo.collector.classifierTrainer[deviceMyo.collector.classifier_selected_class_index][deviceMyo.collector.window_index][deviceMyo.collector.feature_index]
						= deviceMyo.collector.FeatEMG[i][j];
					deviceMyo.collector.feature_index++;

					// Sensor1FeaT1, Sens2Feat1, SEns3Feat1, ... // Sensor1Feat2, Sens2Feat2..etc

				}

			}

		}

		deviceMyo.collector.feature_index = 0;
		deviceMyo.collector.window_index++;

		if (deviceMyo.collector.window_index == maxWindowNumber || deviceMyo.collector.window_index == (int)numericUpDown4->Value) {

			Myo_app::MyForm::disarm_trainer();



		}
		///////////////////////////
		/*
		if (avg_mav >= (float)threshold_mmav && armed) {

		for (int i = 0; i < FtNm; i++) {

		for (int j = 0; j < numSensors; j++) {

		classifierTrainer[classifier_selected_class_index][window_index][feature_index] = FeatEMG[i][j];
		feature_index++;
		// Sensor1FeaT1, Sens2Feat1, SEns3Feat1, ... // Sensor1Feat2, Sens2Feat2..etc
		}

		}

		feature_index = 0;
		window_index++;

		}

		if (window_index == maxWindowNumber) {
		armed = false;
		numWC[classifier_selected_class_index] = window_index;
		window_index = 0;

		}


		*/


	}



}

void Myo_app::MyForm::svm_create_training_percentage()
{

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	HANDLE h = CreateFile("C:\\Users\\admin\\Desktop\\training_percentage.txt",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.dwFlags |= STARTF_USESTDHANDLES;
	si.hStdInput = NULL;
	si.hStdError = h;
	si.hStdOutput = h;


	//creats a model from training data file
	String^ systeminput2;
	/*
	systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-train.exe -v 10 -t " + svm_kernel_type + " "
	+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt";
	*/

	systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe " + folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt "
		+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + ".txt.model "
		+ folderBrowserDialog2->SelectedPath + "\\output.txt ";

	~svm_kernel_type;

	std::string systeminput = context.marshal_as<std::string>(systeminput2);
	const char* systeminput3 = systeminput.c_str();
	char* systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);

	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, TRUE, // db FALSE
		CREATE_NO_WINDOW, //db
		NULL, NULL,
		&si,
		&pi
		);

	// get test percent for first half
	systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe " + folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_A.txt "
		+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_B.txt.model "
		+ folderBrowserDialog2->SelectedPath + "\\output.txt ";


	systeminput = context.marshal_as<std::string>(systeminput2);
	systeminput3 = systeminput.c_str();
	systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);

	HANDLE j = CreateFile("C:\\Users\\admin\\Desktop\\testing_percentage_1.txt",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	si.hStdError = j;
	si.hStdOutput = j;

	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, TRUE, // db FALSE
		CREATE_NO_WINDOW, //db
		NULL, NULL,
		&si,
		&pi
		);

	// get test percent for second half
	systeminput2 = "C:\\Users\\admin\\Desktop\\libsvm-3.20\\libsvm-3.20\\windows\\svm-predict.exe " + folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_B.txt "
		+ folderBrowserDialog2->SelectedPath + "\\" + textBox36->Text + "_A.txt.model "
		+ folderBrowserDialog2->SelectedPath + "\\output.txt ";


	systeminput = context.marshal_as<std::string>(systeminput2);
	systeminput3 = systeminput.c_str();
	systeminputFinal = new char[systeminput.length() + 1];
	strcpy(systeminputFinal, systeminput3);

	HANDLE k = CreateFile("C:\\Users\\admin\\Desktop\\testing_percentage_2.txt",
		FILE_APPEND_DATA,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		&sa,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	si.hStdError = k;
	si.hStdOutput = k;

	CreateProcess(
		NULL,
		systeminputFinal,
		NULL, NULL, TRUE, // db FALSE
		CREATE_NO_WINDOW, //db
		NULL, NULL,
		&si,
		&pi
		);

	accuracy_file_created = 1;


}

void Myo_app::MyForm::get_accuracy()
{

	// file handler for training accuracy
	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\training_percentage.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	ifile2.open(stdLDAPredictInputFileName);

	// file handler for testing accuracy 1
	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\testing_percentage_1.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	ifile1.open(stdLDAPredictInputFileName);

	// file handler for testing accuracy 2
	LDAPredictInputFileName = folderBrowserDialog2->SelectedPath + "\\testing_percentage_2.txt";
	stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
	ifile3.open(stdLDAPredictInputFileName);

	std::string training_accuracy = "NULL";
	std::string testing_accuracy_1 = "NULL";
	std::string testing_accuracy_2 = "NULL";

	// retrieve training accuracy from file
	if (ifile2.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			ifile2 >> training_accuracy;

		}

	}

	ifile2.close();

	// retrieve testing accuracy from file
	if (ifile1.is_open()) {
		for (int i = 0; i < 3; i++)
		{
			ifile1 >> testing_accuracy_1;
		}
	}
	ifile1.close();

	if (ifile3.is_open()) {
		for (int i = 0; i < 3; i++)
		{
			ifile3 >> testing_accuracy_2;
		}
	}
	ifile3.close();

	testing_accuracy_1.pop_back();
	testing_accuracy_1.pop_back();
	float testing1 = 0.000;
	float testing2 = 0.000;
	try {

		testing1 = stof(testing_accuracy_1);
		testing2 = stof(testing_accuracy_2);

	}
	catch (...) {
		textBox39->Text = "ERROR";
	}


	float average = (testing1 + testing2) / (float)2.000;

	// training accuracy
	String^ data2 = gcnew String(training_accuracy.c_str());
	textBox38->Text = data2;

	// testing accuracy
	textBox39->Text = "" + average + "%";

}

void Myo_app::MyForm::disarm_trainer()
{

	deviceMyo.collector.armed = false;

	deviceMyo.collector.numWC[deviceMyo.collector.classifier_selected_class_index] = deviceMyo.collector.window_index;

	//deviceMyo.collector.window_index = 0;

	button8->Text = "Train";

}

void Myo_app::MyForm::lda_driver()
{
	// save gesture names
	model_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + ".labels.txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(model_name);
	fileLDARecord.open(stdRecordLDAFileName);

	for (int i = 0; i < deviceMyo.collector.currentTotalClasses; i++)
	{

		fileLDARecord << gestureNames[i] << " " << pictures[i] << "\n";
	}
	fileLDARecord.close();


	// train LDA:
	lda.run_train(deviceMyo.collector.classifierTrainer, deviceMyo.collector.numWC, maxFeatures, deviceMyo.collector.currentTotalClasses); // Train LDA using feature matrix Xvec2, window # std::vector WinNums2, and feature dimension fd2.

																																		   // get LDA accuracy (2 types):
	textBox38->Text = "" + lda.getTrainAccuracy();
	textBox39->Text = "" + lda.getTestAccuracy();


}

void Myo_app::MyForm::run_classifier()
{
	
	// controlled by "start classifer" and "stop classifier" buttons
	if (comboBox12->SelectedIndex <= 4) { 
		svm_predict(); 
	};

	if (comboBox12->SelectedIndex > 4 && comboBox12->SelectedIndex <= 9) {
		svm_predict_2();
	};

	//becca lda prediction called
	if (comboBox12->SelectedIndex == 10) { 
		lda_classify_predict(); 
	};

}


[STAThread]
int main(array<String^>^ args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Myo_app::MyForm form;
	Application::Run(%form);

	return 0;
}

