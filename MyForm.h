#include "INCLUSIONS.h"
#include "Device.h"
#include "LDA.h"

static Device deviceMyo;

#define input 1
#define imu 2
#define emg 3
#define feature 4
#define classifier 5
#define output 6
#define thickness 4

#pragma once

/*
Text Comment Flags
DB - Debug purposes, DELETE
TH - equations, stuff for written report
NA - Not fully functioning
RF - Code working but can be optimized a lot
YF - Code working, minimal improvements may be necessary
*/

int tabSelected;

LDA lda;

time_t currentTime;
struct tm *localTime;

int recordSeconds = 0;
int recordMinutes = 0;
int recordHours = 0;

//Checks if any myo is connected for recording playback
bool myoStreaming = false;
bool twoMyos = false;
bool fileOpened = false;

bool saveLDA = false;

bool playbackLoop = true;
bool endtimer1 = false;

int rrate = 50; // default refresh rate of hub.run

int lineIndex = 0;

bool record = false;
//bool playBack = false;

int maxNumberLinesEmgPlayback = 1; // counter for playback status bar
int maxNumberLinesImuPlayback = 0;

int currentNumberLinesEmgPlayback = 0;
int currentNumberLinesImuPlayback = 0;

int percentagePlayback = 0;

bool placeMarkerEMG = false; //user turns on to place a marker then flag goes false when marker placed on file
bool placeMarkerIMU = false;

bool onComboBox4Change = false;
bool onComboBox5Change = false;

int accuracy_file_created = 0;

int selectedChart_Cbox4 = 0; //IMU chart 6 starts on myo 1 ori
int selectedChart_Cbox5 = 3; //imu chart 5 starts on myo2 ori
int selectedChart_Cbox11 = 0;

int ite;
int xmin;
int xmax;

int iteration_over = 0;

bool classify = false;

int num_features_used = 4;

int svm_kernel_type = 0;


// feature related variables
float calcMAV();
/*
	test20.collector2.FeatV[0]+=abs(Data[i]);
	test20.collector2.FeatV[1]+-abs(Data[i]-Data[i-1]);
	test20.collector2.FeatV
*/
float calcWAVE();
float calcZero();
float calcTurn();



// File Related Variables
std::ofstream fileEMGRecord;
std::ofstream fileIMURecord;
std::ofstream fileLDARecord;
std::ofstream fileLDAPredictInput;

// reusable file handlers
std::ofstream ofile1;
std::ofstream ofile2;
std::ofstream ofile3;

std::ifstream openEMGFile; //for open file dialogue
std::ifstream openIMUFile;
std::ifstream openLDAFile;
std::ifstream openLDAPredictionOutput;

// reusable file handlers
std::ifstream ifile1;
std::ifstream ifile2;
std::ifstream ifile3;

std::string stdOpenEMGFile; //for converting user selection to string
std::string stdOpenIMUFile;
std::string stdOpenLDAFile;

std::string stdRecordEMGFileName;
std::string stdRecordIMUFileName;
std::string stdRecordLDAFileName;
std::string stdLDAPredictInputFileName;
//

//array for directory storage
std::string pictures[30] = { "0" };

//classifier related
std::string gestureNames[maxClasses] = {"null"};



namespace Myo_app{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	//using namespace hellomyoVisualStudio2013;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		void init_EMG_charts();

		// testing purposes - graph on classifier tab
		void init_mmav_chart(void);
		
		void Display_EMG(DataCollector val); //EMG Display

		void playbackEMG(std::ifstream& openEMGFile);
		void playbackIMU(std::ifstream& openIMUFile);
		
		void init_IMU_charts(void);

		void recordData(int it_emg_view, int it_imu_view);

		void Display_ori_1(DataCollector val, Chart^ chart);
		void Display_accel_1(DataCollector val, Chart^ chart);
		void Display_gyro_1(DataCollector val, Chart^ chart);

		void Display_ori_2(DataCollector val, Chart^ chart);
		void Display_accel_2(DataCollector val, Chart^ chart);
		void Display_gyro_2(DataCollector val, Chart^ chart);

		void Display_IMU_chart_area(ComboBox^ cbox, Chart^ chart);
		void Relabel_IMU_chart_area(ComboBox^ cbox, Chart^ chart);
		void Relabel_EMG_chart_area(Chart^ chart);

		void mmav_increment_axis(void);

		void mmav_display_line(DataCollector val);

		void printEMG(int it_emg_view);

		void printIMU(int it_imu_view);

		void updateStatus();

		void Display_IMU_CB4(Chart^ chart);

		void display_IMU_CB11_CH7();

		//classifier functions
		void svm_create_model();

		void svm_predict();

		void svm_predict_2();
		
		//becca functions
		void lda_classify_train();

		void lda_classify_predict();

		void classifier_training();

		void svm_create_training_percentage();

		void get_accuracy();

		void disarm_trainer();

		void lda_driver();

		void run_classifier();
	

		array<bool> ^ clear_state_feature;

		array<Chart^, 1> ^ cc_imu = gcnew array<Chart^, 1>(3);
		array<DataPoint^, 2> ^ point_gyro_1 = gcnew array<DataPoint^, 2>(3, 128);
		array<DataPoint^, 2> ^ point_accel_1 = gcnew array<DataPoint^, 2>(3, 128);
		array<DataPoint^, 2> ^ point_ori_1 = gcnew array<DataPoint^, 2>(3, 128);

		array<DataPoint^, 2> ^ point_gyro_2 = gcnew array<DataPoint^, 2>(3, 128);
		array<DataPoint^, 2> ^ point_accel_2 = gcnew array<DataPoint^, 2>(3, 128);
		array<DataPoint^, 2> ^ point_ori_2 = gcnew array<DataPoint^, 2>(3, 128);

		array<DataPoint^, 2> ^ avg_point_ori_1 = gcnew array<DataPoint^, 2>(3, 128);

	private: System::Windows::Forms::TabPage^  tabPage5;
	public:
	private: System::Windows::Forms::Button^  button11;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox31;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  label84;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label83;
	private: System::Windows::Forms::Label^  label82;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TabPage^  tabPage6;
	private: System::Windows::Forms::TabPage^  tabPage4;







	private: System::Windows::Forms::TabPage^  tabPage3;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Button^  button30;
	private: System::Windows::Forms::Button^  button31;
	private: System::Windows::Forms::GroupBox^  groupBox11;
	private: System::Windows::Forms::TextBox^  textBox54;
	private: System::Windows::Forms::Label^  label148;
	private: System::Windows::Forms::TextBox^  textBox53;
	private: System::Windows::Forms::TextBox^  textBox52;
	private: System::Windows::Forms::TextBox^  textBox15;
	private: System::Windows::Forms::Label^  label147;
	private: System::Windows::Forms::TextBox^  textBox51;
	private: System::Windows::Forms::TextBox^  textBox50;
	private: System::Windows::Forms::Label^  label137;
	private: System::Windows::Forms::Label^  label146;
	private: System::Windows::Forms::Label^  label138;
	private: System::Windows::Forms::Label^  label144;
	private: System::Windows::Forms::Label^  label141;
	private: System::Windows::Forms::TextBox^  textBox49;
	private: System::Windows::Forms::Label^  label142;
	private: System::Windows::Forms::TextBox^  textBox48;










	private: System::Windows::Forms::Label^  label78;




	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Button^  button29;
	private: System::Windows::Forms::Button^  button28;
	private: System::Windows::Forms::GroupBox^  groupBox12;
	private: System::Windows::Forms::GroupBox^  groupBox13;
	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::TextBox^  textBox17;
	private: System::Windows::Forms::Label^  label34;
	private: System::Windows::Forms::TextBox^  textBox21;
	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::TextBox^  textBox23;
	private: System::Windows::Forms::GroupBox^  groupBox14;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Label^  label41;
	private: System::Windows::Forms::TextBox^  textBox24;
	private: System::Windows::Forms::TextBox^  textBox25;
	private: System::Windows::Forms::Label^  label42;
	private: System::Windows::Forms::Label^  label43;
	private: System::Windows::Forms::TextBox^  textBox26;
	private: System::Windows::Forms::GroupBox^  groupBox15;
	private: System::Windows::Forms::Label^  label44;
	private: System::Windows::Forms::Label^  label45;
	private: System::Windows::Forms::Label^  label46;
	private: System::Windows::Forms::Label^  label47;
	private: System::Windows::Forms::Label^  label48;
	private: System::Windows::Forms::TextBox^  textBox27;
	private: System::Windows::Forms::TextBox^  textBox28;
	private: System::Windows::Forms::Label^  label49;
	private: System::Windows::Forms::TextBox^  textBox32;
	private: System::Windows::Forms::GroupBox^  groupBox10;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox12;
	private: System::Windows::Forms::TextBox^  textBox13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TabPage^  tabPage1;

	private: System::Windows::Forms::TextBox^  textBox34;
	private: System::Windows::Forms::TextBox^  textBox33;
	private: System::Windows::Forms::Label^  label51;
	private: System::Windows::Forms::Label^  label50;
	private: System::Windows::Forms::GroupBox^  groupBox8;


	private: System::Windows::Forms::Label^  label39;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::Button^  button23;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::Button^  button13;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::TextBox^  textBox16;
	private: System::Windows::Forms::TextBox^  textBox19;
	private: System::Windows::Forms::Button^  button18;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::Button^  button22;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::CheckBox^  checkBox9;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::Button^  button20;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::TextBox^  textBox20;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::TextBox^  textBox18;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Button^  button32;
	private: System::Windows::Forms::GroupBox^  groupBox16;

	private: System::Windows::Forms::Button^  button26;
	private: System::Windows::Forms::Label^  label52;
	private: System::Windows::Forms::ProgressBar^  progressBar2;
	private: System::Windows::Forms::Button^  buttonConnect1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button25;
	private: System::Windows::Forms::GroupBox^  groupBox9;
	private: System::Windows::Forms::Button^  button27;
	private: System::Windows::Forms::Label^  label53;
	private: System::Windows::Forms::ProgressBar^  progressBar3;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Button^  button21;
	private: System::Windows::Forms::TextBox^  textBox22;
	private: System::Windows::Forms::Button^  button24;
	private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::ComboBox^  comboBox3;
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::ComboBox^  comboBox4;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart5;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart6;
private: System::Windows::Forms::ComboBox^  comboBox5;
private: System::Windows::Forms::Label^  label58;
private: System::Windows::Forms::Label^  label64;
private: System::Windows::Forms::Label^  label63;
private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::Label^  label62;
private: System::Windows::Forms::Label^  label60;
private: System::Windows::Forms::Label^  label59;
private: System::Windows::Forms::Label^  label55;
private: System::Windows::Forms::Label^  label57;
private: System::Windows::Forms::Label^  label56;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label23;


private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart4;
private: System::Windows::Forms::CheckBox^  checkBox5;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
private: System::Windows::Forms::GroupBox^  groupBox17;
private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
private: System::Windows::Forms::ComboBox^  comboBox6;
private: System::Windows::Forms::ComboBox^  comboBox7;
private: System::Windows::Forms::ComboBox^  comboBox8;
private: System::Windows::Forms::ComboBox^  comboBox9;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::CheckBox^  checkBox4;
private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::CheckBox^  checkBox3;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::Button^  button17;
private: System::Windows::Forms::Button^  button15;
private: System::Windows::Forms::Button^  button16;
private: System::Windows::Forms::Button^  button14;
private: System::Windows::Forms::Label^  label67;
private: System::Windows::Forms::Label^  label65;
private: System::Windows::Forms::Label^  label66;
private: System::Windows::Forms::Label^  label54;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart3;
private: System::Windows::Forms::CheckBox^  checkBox7;
private: System::Windows::Forms::Label^  label68;
private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
private: System::Windows::Forms::GroupBox^  groupBox18;
private: System::Windows::Forms::TextBox^  textBox14;
private: System::Windows::Forms::ComboBox^  comboBox10;
private: System::Windows::Forms::TextBox^  textBox30;
private: System::Windows::Forms::TextBox^  textBox29;
private: System::Windows::Forms::Label^  label72;
private: System::Windows::Forms::Label^  label71;
private: System::Windows::Forms::Label^  label70;
private: System::Windows::Forms::Label^  label69;
private: System::Windows::Forms::Button^  button10;
private: System::Windows::Forms::Button^  button9;
private: System::Windows::Forms::Button^  button8;

private: System::Windows::Forms::GroupBox^  groupBox19;

private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart7;
private: System::Windows::Forms::Label^  label73;
private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
private: System::Windows::Forms::ComboBox^  comboBox11;

private: System::Windows::Forms::Label^  label75;
private: System::Windows::Forms::TextBox^  textBox35;
private: System::Windows::Forms::Label^  label76;
private: System::Windows::Forms::Button^  button12;
private: System::Windows::Forms::Label^  label77;
private: System::Windows::Forms::TextBox^  textBox36;
private: System::Windows::Forms::Button^  button19;
private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog2;
private: System::Windows::Forms::TextBox^  textBox37;
private: System::Windows::Forms::Button^  button33;

private: System::Windows::Forms::Label^  label74;

private: System::Windows::Forms::Label^  label80;
private: System::Windows::Forms::ComboBox^  comboBox12;


private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Label^  label85;
private: System::Windows::Forms::TextBox^  textBox38;
private: System::Windows::Forms::TextBox^  textBox39;
private: System::Windows::Forms::Label^  label87;
private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
private: System::Windows::Forms::Label^  label88;

private: System::Windows::Forms::Button^  button34;
private: System::Windows::Forms::PictureBox^  pictureBox1;

private: System::Windows::Forms::Button^  button35;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog3;
private: System::Windows::Forms::Button^  button36;

	public:
		 array<Chart^, 1> ^ chartEMG = gcnew array<Chart^, 1>(4); //db for charts
	public:

		MyForm(void)
		{
			InitializeComponent();
			chartEMG[0] = chart1;
			chartEMG[1] = chart2;

			cc_imu[0] = chart6;
			cc_imu[1] = chart5;
			cc_imu[2] = chart7;

			clear_state_feature = gcnew array<bool>(8){ false };

			//
			//TODO: Add the constructor code here
			//
		}
	

	public:
		msclr::interop::marshal_context context;//used for converting to strings

		System::String ^userRecordDirectory; //for user file browser dialogue
		String^ LDARecordDirectory;
		String^ PictureDirectory;
		String^ recordingFileName;
		
		String^ model_name;
		String^ model_A_name;
		String^ model_B_name;
		String^ training_data_name;
		String^ LDAPredictInputFileName;

	public:
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog2;
private: System::Windows::Forms::Timer^  RecordTimer;
	public:

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	//private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
private: System::ComponentModel::IContainer^  components;
	protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
 

#pragma region Windows Form Designer generated code
		//Every gui element attribute list, properties
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->RecordTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox31 = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label84 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label83 = (gcnew System::Windows::Forms::Label());
			this->label82 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->tabPage6 = (gcnew System::Windows::Forms::TabPage());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox19 = (gcnew System::Windows::Forms::GroupBox());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
			this->comboBox11 = (gcnew System::Windows::Forms::ComboBox());
			this->chart7 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
			this->button36 = (gcnew System::Windows::Forms::Button());
			this->button35 = (gcnew System::Windows::Forms::Button());
			this->textBox39 = (gcnew System::Windows::Forms::TextBox());
			this->button34 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label87 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label85 = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->textBox38 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox12 = (gcnew System::Windows::Forms::ComboBox());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->button33 = (gcnew System::Windows::Forms::Button());
			this->textBox36 = (gcnew System::Windows::Forms::TextBox());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->textBox35 = (gcnew System::Windows::Forms::TextBox());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label88 = (gcnew System::Windows::Forms::Label());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox10 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->chart4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox37 = (gcnew System::Windows::Forms::TextBox());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->chart3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->comboBox7 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox9 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox8 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button30 = (gcnew System::Windows::Forms::Button());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox54 = (gcnew System::Windows::Forms::TextBox());
			this->label148 = (gcnew System::Windows::Forms::Label());
			this->textBox53 = (gcnew System::Windows::Forms::TextBox());
			this->textBox52 = (gcnew System::Windows::Forms::TextBox());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->label147 = (gcnew System::Windows::Forms::Label());
			this->textBox51 = (gcnew System::Windows::Forms::TextBox());
			this->textBox50 = (gcnew System::Windows::Forms::TextBox());
			this->label137 = (gcnew System::Windows::Forms::Label());
			this->label146 = (gcnew System::Windows::Forms::Label());
			this->label138 = (gcnew System::Windows::Forms::Label());
			this->label144 = (gcnew System::Windows::Forms::Label());
			this->label141 = (gcnew System::Windows::Forms::Label());
			this->textBox49 = (gcnew System::Windows::Forms::TextBox());
			this->label142 = (gcnew System::Windows::Forms::Label());
			this->textBox48 = (gcnew System::Windows::Forms::TextBox());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->chart5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->textBox28 = (gcnew System::Windows::Forms::TextBox());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->textBox32 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->textBox34 = (gcnew System::Windows::Forms::TextBox());
			this->textBox33 = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button32 = (gcnew System::Windows::Forms::Button());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->buttonConnect1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->progressBar3 = (gcnew System::Windows::Forms::ProgressBar());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->folderBrowserDialog2 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog3 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabPage5->SuspendLayout();
			this->tabPage6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox19->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart7))->BeginInit();
			this->groupBox18->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
			this->groupBox17->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->groupBox11->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox6->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart6))->BeginInit();
			this->groupBox12->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->groupBox14->SuspendLayout();
			this->groupBox15->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 20;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"Select File";
			this->openFileDialog1->Filter = L" EMG Files (*.EMG.*)|*.EMG.*|csv (*.csv) and txt (*.txt)|*.txt; *.csv|All files ("
				L"*.*)|*.*";
			this->openFileDialog1->Title = L"Load EMG Data File";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->SelectedPath = L"C:\\Users\\admin\\Desktop\\COMETS\\GUIinProgress\\samples\\test_runs";
			this->folderBrowserDialog1->HelpRequest += gcnew System::EventHandler(this, &MyForm::folderBrowserDialog1_HelpRequest);
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"Select File";
			this->openFileDialog2->Filter = L" IMU Files (*.IMU.*)|*.IMU.*|csv (*.csv) and txt (*.txt)|*.txt; *.csv|All files ("
				L"*.*)|*.*";
			this->openFileDialog2->Title = L"Load IMU Data File";
			// 
			// RecordTimer
			// 
			this->RecordTimer->Interval = 1000;
			this->RecordTimer->Tick += gcnew System::EventHandler(this, &MyForm::RecordTimer_Tick);
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->button11);
			this->tabPage5->Controls->Add(this->textBox9);
			this->tabPage5->Controls->Add(this->textBox31);
			this->tabPage5->Controls->Add(this->label20);
			this->tabPage5->Controls->Add(this->button6);
			this->tabPage5->Controls->Add(this->button5);
			this->tabPage5->Controls->Add(this->label84);
			this->tabPage5->Controls->Add(this->button4);
			this->tabPage5->Controls->Add(this->comboBox2);
			this->tabPage5->Controls->Add(this->label83);
			this->tabPage5->Controls->Add(this->label82);
			this->tabPage5->Controls->Add(this->comboBox1);
			this->tabPage5->Controls->Add(this->button7);
			this->tabPage5->Location = System::Drawing::Point(4, 40);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1182, 693);
			this->tabPage5->TabIndex = 8;
			this->tabPage5->Text = L"Output";
			this->tabPage5->UseVisualStyleBackColor = true;
			this->tabPage5->Enter += gcnew System::EventHandler(this, &MyForm::tabPage5_Enter);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(279, 25);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(111, 23);
			this->button11->TabIndex = 13;
			this->button11->Text = L"Start Predicting";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MyForm::button11_Click);
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(157, 25);
			this->textBox9->Name = L"textBox9";
			this->textBox9->ReadOnly = true;
			this->textBox9->Size = System::Drawing::Size(100, 20);
			this->textBox9->TabIndex = 12;
			// 
			// textBox31
			// 
			this->textBox31->Location = System::Drawing::Point(450, 27);
			this->textBox31->Name = L"textBox31";
			this->textBox31->ReadOnly = true;
			this->textBox31->Size = System::Drawing::Size(100, 20);
			this->textBox31->TabIndex = 6;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(19, 28);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(132, 13);
			this->label20->TabIndex = 11;
			this->label20->Text = L"Current Perceived Gesture";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(199, 171);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(175, 23);
			this->button6->TabIndex = 9;
			this->button6->Text = L"Enable Myo Mouse Control";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(453, 194);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(111, 23);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Disable All Bindings";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// label84
			// 
			this->label84->AutoSize = true;
			this->label84->Location = System::Drawing::Point(450, 8);
			this->label84->Name = L"label84";
			this->label84->Size = System::Drawing::Size(40, 13);
			this->label84->TabIndex = 7;
			this->label84->Text = L"Status:";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(743, 96);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Bind";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(573, 99);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 4;
			// 
			// label83
			// 
			this->label83->AutoSize = true;
			this->label83->Location = System::Drawing::Point(443, 101);
			this->label83->Name = L"label83";
			this->label83->Size = System::Drawing::Size(107, 13);
			this->label83->TabIndex = 3;
			this->label83->Text = L"Select Key Binding(s)";
			// 
			// label82
			// 
			this->label82->AutoSize = true;
			this->label82->Location = System::Drawing::Point(196, 102);
			this->label82->Name = L"label82";
			this->label82->Size = System::Drawing::Size(77, 13);
			this->label82->TabIndex = 2;
			this->label82->Text = L"Select Gesture";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(279, 99);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 1;
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(199, 171);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(175, 23);
			this->button7->TabIndex = 10;
			this->button7->Text = L"Disable Myo Mouse Control";
			this->button7->UseVisualStyleBackColor = true;
			// 
			// tabPage6
			// 
			this->tabPage6->Controls->Add(this->pictureBox1);
			this->tabPage6->Controls->Add(this->groupBox19);
			this->tabPage6->Controls->Add(this->groupBox18);
			this->tabPage6->Controls->Add(this->groupBox17);
			this->tabPage6->Controls->Add(this->textBox37);
			this->tabPage6->Controls->Add(this->label74);
			this->tabPage6->Location = System::Drawing::Point(4, 40);
			this->tabPage6->Name = L"tabPage6";
			this->tabPage6->Padding = System::Windows::Forms::Padding(3);
			this->tabPage6->Size = System::Drawing::Size(1182, 693);
			this->tabPage6->TabIndex = 5;
			this->tabPage6->Text = L"Classifier";
			this->tabPage6->UseVisualStyleBackColor = true;
			this->tabPage6->Click += gcnew System::EventHandler(this, &MyForm::tabPage6_Click);
			this->tabPage6->Enter += gcnew System::EventHandler(this, &MyForm::tabPage6_Enter);
			this->tabPage6->Leave += gcnew System::EventHandler(this, &MyForm::tabPage6_Leave);
			// 
			// pictureBox1
			// 
			this->pictureBox1->AccessibleRole = System::Windows::Forms::AccessibleRole::ScrollBar;
			this->pictureBox1->Location = System::Drawing::Point(83, 399);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(280, 280);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 25;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox19
			// 
			this->groupBox19->Controls->Add(this->label73);
			this->groupBox19->Controls->Add(this->numericUpDown6);
			this->groupBox19->Controls->Add(this->comboBox11);
			this->groupBox19->Controls->Add(this->chart7);
			this->groupBox19->Location = System::Drawing::Point(464, 349);
			this->groupBox19->Name = L"groupBox19";
			this->groupBox19->Size = System::Drawing::Size(715, 338);
			this->groupBox19->TabIndex = 24;
			this->groupBox19->TabStop = false;
			this->groupBox19->Text = L"IMU";
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Location = System::Drawing::Point(6, 43);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(82, 13);
			this->label73->TabIndex = 40;
			this->label73->Text = L"# Samples Avg.";
			// 
			// numericUpDown6
			// 
			this->numericUpDown6->Location = System::Drawing::Point(94, 43);
			this->numericUpDown6->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown6->Name = L"numericUpDown6";
			this->numericUpDown6->Size = System::Drawing::Size(129, 20);
			this->numericUpDown6->TabIndex = 39;
			this->numericUpDown6->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// comboBox11
			// 
			this->comboBox11->FormattingEnabled = true;
			this->comboBox11->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"1 Ori", L"1 Gyr", L"1 Acc", L"2 Ori", L"2 Gyr",
					L"2 Acc"
			});
			this->comboBox11->Location = System::Drawing::Point(94, 16);
			this->comboBox11->Name = L"comboBox11";
			this->comboBox11->Size = System::Drawing::Size(129, 21);
			this->comboBox11->TabIndex = 38;
			this->comboBox11->Text = L"Select Graph...";
			this->comboBox11->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox11_SelectionChangeCommitted);
			// 
			// chart7
			// 
			this->chart7->BorderlineColor = System::Drawing::Color::Black;
			this->chart7->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::DashDot;
			this->chart7->Location = System::Drawing::Point(307, 19);
			this->chart7->Name = L"chart7";
			this->chart7->Size = System::Drawing::Size(360, 313);
			this->chart7->TabIndex = 0;
			this->chart7->Text = L"chart7";
			// 
			// groupBox18
			// 
			this->groupBox18->Controls->Add(this->button36);
			this->groupBox18->Controls->Add(this->button35);
			this->groupBox18->Controls->Add(this->textBox39);
			this->groupBox18->Controls->Add(this->button34);
			this->groupBox18->Controls->Add(this->numericUpDown4);
			this->groupBox18->Controls->Add(this->label87);
			this->groupBox18->Controls->Add(this->button1);
			this->groupBox18->Controls->Add(this->label85);
			this->groupBox18->Controls->Add(this->label80);
			this->groupBox18->Controls->Add(this->textBox38);
			this->groupBox18->Controls->Add(this->comboBox12);
			this->groupBox18->Controls->Add(this->button19);
			this->groupBox18->Controls->Add(this->label77);
			this->groupBox18->Controls->Add(this->button33);
			this->groupBox18->Controls->Add(this->textBox36);
			this->groupBox18->Controls->Add(this->button12);
			this->groupBox18->Controls->Add(this->label75);
			this->groupBox18->Controls->Add(this->textBox35);
			this->groupBox18->Controls->Add(this->textBox30);
			this->groupBox18->Controls->Add(this->textBox29);
			this->groupBox18->Controls->Add(this->label88);
			this->groupBox18->Controls->Add(this->label72);
			this->groupBox18->Controls->Add(this->label71);
			this->groupBox18->Controls->Add(this->label70);
			this->groupBox18->Controls->Add(this->label69);
			this->groupBox18->Controls->Add(this->button10);
			this->groupBox18->Controls->Add(this->button9);
			this->groupBox18->Controls->Add(this->button8);
			this->groupBox18->Controls->Add(this->textBox14);
			this->groupBox18->Controls->Add(this->comboBox10);
			this->groupBox18->Location = System::Drawing::Point(6, 6);
			this->groupBox18->Name = L"groupBox18";
			this->groupBox18->Size = System::Drawing::Size(452, 337);
			this->groupBox18->TabIndex = 23;
			this->groupBox18->TabStop = false;
			this->groupBox18->Text = L"Gesture";
			// 
			// button36
			// 
			this->button36->Location = System::Drawing::Point(336, 117);
			this->button36->Name = L"button36";
			this->button36->Size = System::Drawing::Size(107, 23);
			this->button36->TabIndex = 35;
			this->button36->Text = L"Save Training Data";
			this->button36->UseVisualStyleBackColor = true;
			this->button36->Click += gcnew System::EventHandler(this, &MyForm::button36_Click);
			// 
			// button35
			// 
			this->button35->Location = System::Drawing::Point(362, 301);
			this->button35->Name = L"button35";
			this->button35->Size = System::Drawing::Size(81, 23);
			this->button35->TabIndex = 27;
			this->button35->Text = L"Load Picture";
			this->button35->UseVisualStyleBackColor = true;
			this->button35->Click += gcnew System::EventHandler(this, &MyForm::button35_Click_2);
			// 
			// textBox39
			// 
			this->textBox39->Location = System::Drawing::Point(112, 296);
			this->textBox39->Name = L"textBox39";
			this->textBox39->ReadOnly = true;
			this->textBox39->Size = System::Drawing::Size(100, 20);
			this->textBox39->TabIndex = 27;
			// 
			// button34
			// 
			this->button34->Location = System::Drawing::Point(336, 89);
			this->button34->Name = L"button34";
			this->button34->Size = System::Drawing::Size(107, 23);
			this->button34->TabIndex = 26;
			this->button34->Text = L"Select Picture";
			this->button34->UseVisualStyleBackColor = true;
			this->button34->Click += gcnew System::EventHandler(this, &MyForm::button34_Click_1);
			// 
			// numericUpDown4
			// 
			this->numericUpDown4->Location = System::Drawing::Point(405, 18);
			this->numericUpDown4->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1024, 0, 0, 0 });
			this->numericUpDown4->Name = L"numericUpDown4";
			this->numericUpDown4->Size = System::Drawing::Size(41, 20);
			this->numericUpDown4->TabIndex = 34;
			this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// label87
			// 
			this->label87->AutoSize = true;
			this->label87->Location = System::Drawing::Point(10, 301);
			this->label87->Name = L"label87";
			this->label87->Size = System::Drawing::Size(93, 13);
			this->label87->TabIndex = 26;
			this->label87->Text = L"Testing Accuracy:";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(214, 118);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(116, 23);
			this->button1->TabIndex = 33;
			this->button1->Text = L"Testing Accuracy";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_2);
			// 
			// label85
			// 
			this->label85->AutoSize = true;
			this->label85->Location = System::Drawing::Point(10, 275);
			this->label85->Name = L"label85";
			this->label85->Size = System::Drawing::Size(96, 13);
			this->label85->TabIndex = 26;
			this->label85->Text = L"Training Accuracy:";
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->Location = System::Drawing::Point(10, 121);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(51, 13);
			this->label80->TabIndex = 31;
			this->label80->Text = L"Classifier:";
			// 
			// textBox38
			// 
			this->textBox38->Location = System::Drawing::Point(112, 272);
			this->textBox38->Name = L"textBox38";
			this->textBox38->ReadOnly = true;
			this->textBox38->Size = System::Drawing::Size(100, 20);
			this->textBox38->TabIndex = 25;
			// 
			// comboBox12
			// 
			this->comboBox12->FormattingEnabled = true;
			this->comboBox12->Items->AddRange(gcnew cli::array< System::Object^  >(11) {
				L"libsvm - linear_C-svc", L"libsvm - polynomial_C-svc",
					L"libsvm - radial_C-svc", L"libsvm - sigmoid_C-svc", L"libsvm - precomuted kernel_C-svc", L"libsvm - linear_nu-svc", L"libsvm - polynomial_nu-svc",
					L"libsvm - radial_nu-svc", L"libsvm - sigmoid_nu-svc", L"libsvm - precomuted kernel_nu-svc", L"LDA"
			});
			this->comboBox12->Location = System::Drawing::Point(87, 118);
			this->comboBox12->Name = L"comboBox12";
			this->comboBox12->Size = System::Drawing::Size(121, 21);
			this->comboBox12->TabIndex = 30;
			this->comboBox12->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox12_SelectionChangeCommitted);
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(214, 147);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(25, 20);
			this->button19->TabIndex = 15;
			this->button19->Text = L"...";
			this->button19->UseVisualStyleBackColor = true;
			this->button19->Click += gcnew System::EventHandler(this, &MyForm::button19_Click_1);
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->Location = System::Drawing::Point(10, 151);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(70, 13);
			this->label77->TabIndex = 14;
			this->label77->Text = L"Model Name:";
			// 
			// button33
			// 
			this->button33->Location = System::Drawing::Point(77, 198);
			this->button33->Name = L"button33";
			this->button33->Size = System::Drawing::Size(253, 35);
			this->button33->TabIndex = 25;
			this->button33->Text = L"Start Classifier";
			this->button33->UseVisualStyleBackColor = true;
			this->button33->Click += gcnew System::EventHandler(this, &MyForm::button33_Click);
			// 
			// textBox36
			// 
			this->textBox36->Location = System::Drawing::Point(87, 148);
			this->textBox36->Name = L"textBox36";
			this->textBox36->Size = System::Drawing::Size(121, 20);
			this->textBox36->TabIndex = 13;
			// 
			// button12
			// 
			this->button12->Enabled = false;
			this->button12->Location = System::Drawing::Point(244, 146);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(199, 23);
			this->button12->TabIndex = 12;
			this->button12->Text = L"Create Model";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::button12_Click_1);
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->Location = System::Drawing::Point(120, 20);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(40, 13);
			this->label75->TabIndex = 11;
			this->label75->Text = L"Status:";
			// 
			// textBox35
			// 
			this->textBox35->Location = System::Drawing::Point(166, 17);
			this->textBox35->Name = L"textBox35";
			this->textBox35->ReadOnly = true;
			this->textBox35->Size = System::Drawing::Size(56, 20);
			this->textBox35->TabIndex = 10;
			// 
			// textBox30
			// 
			this->textBox30->Location = System::Drawing::Point(287, 17);
			this->textBox30->Name = L"textBox30";
			this->textBox30->ReadOnly = true;
			this->textBox30->Size = System::Drawing::Size(40, 20);
			this->textBox30->TabIndex = 8;
			// 
			// textBox29
			// 
			this->textBox29->Location = System::Drawing::Point(87, 17);
			this->textBox29->Name = L"textBox29";
			this->textBox29->ReadOnly = true;
			this->textBox29->Size = System::Drawing::Size(26, 20);
			this->textBox29->TabIndex = 8;
			// 
			// label88
			// 
			this->label88->AutoSize = true;
			this->label88->Location = System::Drawing::Point(333, 20);
			this->label88->Name = L"label88";
			this->label88->Size = System::Drawing::Size(70, 13);
			this->label88->TabIndex = 7;
			this->label88->Text = L"Max Samples";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(231, 20);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(50, 13);
			this->label72->TabIndex = 7;
			this->label72->Text = L"Samples ";
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(10, 20);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(71, 13);
			this->label71->TabIndex = 7;
			this->label71->Text = L"# of Gestures";
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(10, 61);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(38, 13);
			this->label70->TabIndex = 6;
			this->label70->Text = L"Name:";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(10, 94);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(47, 13);
			this->label69->TabIndex = 5;
			this->label69->Text = L"Gesture:";
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(374, 56);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(69, 23);
			this->button10->TabIndex = 4;
			this->button10->Text = L"Delete All";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(214, 56);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(154, 23);
			this->button9->TabIndex = 2;
			this->button9->Text = L"Add";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button8
			// 
			this->button8->Enabled = false;
			this->button8->Location = System::Drawing::Point(214, 89);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(113, 23);
			this->button8->TabIndex = 3;
			this->button8->Text = L"Train";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click_1);
			// 
			// textBox14
			// 
			this->textBox14->Location = System::Drawing::Point(87, 58);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(121, 20);
			this->textBox14->TabIndex = 1;
			// 
			// comboBox10
			// 
			this->comboBox10->FormattingEnabled = true;
			this->comboBox10->Location = System::Drawing::Point(87, 91);
			this->comboBox10->Name = L"comboBox10";
			this->comboBox10->Size = System::Drawing::Size(121, 21);
			this->comboBox10->TabIndex = 0;
			this->comboBox10->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox10_SelectionChangeCommitted);
			// 
			// groupBox17
			// 
			this->groupBox17->Controls->Add(this->label76);
			this->groupBox17->Controls->Add(this->checkBox5);
			this->groupBox17->Controls->Add(this->label40);
			this->groupBox17->Controls->Add(this->chart4);
			this->groupBox17->Controls->Add(this->numericUpDown1);
			this->groupBox17->Location = System::Drawing::Point(464, 6);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(712, 337);
			this->groupBox17->TabIndex = 22;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"Mean Mean Average Value (MMAV)";
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Location = System::Drawing::Point(387, 23);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(49, 13);
			this->label76->TabIndex = 22;
			this->label76->Text = L"AvgMAV";
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Checked = true;
			this->checkBox5->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox5->Location = System::Drawing::Point(40, 28);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(95, 17);
			this->checkBox5->TabIndex = 19;
			this->checkBox5->Text = L"Display MMAV";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(151, 28);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(54, 13);
			this->label40->TabIndex = 21;
			this->label40->Text = L"Threshold";
			// 
			// chart4
			// 
			this->chart4->BackColor = System::Drawing::Color::Transparent;
			this->chart4->BackSecondaryColor = System::Drawing::Color::White;
			this->chart4->BorderlineColor = System::Drawing::Color::Black;
			this->chart4->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			this->chart4->Location = System::Drawing::Point(40, 45);
			this->chart4->Name = L"chart4";
			this->chart4->Size = System::Drawing::Size(627, 278);
			this->chart4->TabIndex = 18;
			this->chart4->Text = L"chart2";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(211, 21);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 20;
			// 
			// textBox37
			// 
			this->textBox37->Enabled = false;
			this->textBox37->Font = (gcnew System::Drawing::Font(L"Lucida Sans", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox37->ForeColor = System::Drawing::Color::DarkRed;
			this->textBox37->Location = System::Drawing::Point(129, 354);
			this->textBox37->Name = L"textBox37";
			this->textBox37->Size = System::Drawing::Size(193, 39);
			this->textBox37->TabIndex = 26;
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->Location = System::Drawing::Point(66, 365);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(57, 13);
			this->label74->TabIndex = 28;
			this->label74->Text = L"Prediction:";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->label22);
			this->tabPage4->Controls->Add(this->label21);
			this->tabPage4->Controls->Add(this->checkBox4);
			this->tabPage4->Controls->Add(this->checkBox2);
			this->tabPage4->Controls->Add(this->checkBox3);
			this->tabPage4->Controls->Add(this->checkBox1);
			this->tabPage4->Controls->Add(this->button17);
			this->tabPage4->Controls->Add(this->button15);
			this->tabPage4->Controls->Add(this->button16);
			this->tabPage4->Controls->Add(this->button14);
			this->tabPage4->Location = System::Drawing::Point(4, 40);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1182, 693);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"Feature Selection";
			this->tabPage4->UseVisualStyleBackColor = true;
			this->tabPage4->Click += gcnew System::EventHandler(this, &MyForm::tabPage4_Click);
			this->tabPage4->Enter += gcnew System::EventHandler(this, &MyForm::tabPage4_Enter);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(112, 34);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(87, 13);
			this->label22->TabIndex = 133;
			this->label22->Text = L"Use in Classifier\?";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(63, 34);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(43, 13);
			this->label21->TabIndex = 132;
			this->label21->Text = L"Feature";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Location = System::Drawing::Point(143, 205);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(15, 14);
			this->checkBox4->TabIndex = 128;
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(143, 113);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(15, 14);
			this->checkBox2->TabIndex = 129;
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Checked = true;
			this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox3->Location = System::Drawing::Point(143, 161);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(15, 14);
			this->checkBox3->TabIndex = 130;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(143, 69);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 131;
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(49, 200);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(75, 23);
			this->button17->TabIndex = 124;
			this->button17->Text = L"Turn";
			this->button17->UseVisualStyleBackColor = true;
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(49, 108);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(75, 23);
			this->button15->TabIndex = 125;
			this->button15->Text = L"Wavelength";
			this->button15->UseVisualStyleBackColor = true;
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(49, 156);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(75, 23);
			this->button16->TabIndex = 126;
			this->button16->Text = L"Zero";
			this->button16->UseVisualStyleBackColor = true;
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(49, 64);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 127;
			this->button14->Text = L"MAV";
			this->button14->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->label68);
			this->tabPage3->Controls->Add(this->numericUpDown5);
			this->tabPage3->Controls->Add(this->checkBox7);
			this->tabPage3->Controls->Add(this->chart3);
			this->tabPage3->Controls->Add(this->label67);
			this->tabPage3->Controls->Add(this->label65);
			this->tabPage3->Controls->Add(this->label66);
			this->tabPage3->Controls->Add(this->label54);
			this->tabPage3->Controls->Add(this->comboBox7);
			this->tabPage3->Controls->Add(this->comboBox9);
			this->tabPage3->Controls->Add(this->comboBox8);
			this->tabPage3->Controls->Add(this->comboBox6);
			this->tabPage3->Controls->Add(this->numericUpDown3);
			this->tabPage3->Controls->Add(this->numericUpDown2);
			this->tabPage3->Controls->Add(this->chart2);
			this->tabPage3->Controls->Add(this->chart1);
			this->tabPage3->Controls->Add(this->button30);
			this->tabPage3->Controls->Add(this->button31);
			this->tabPage3->Controls->Add(this->groupBox11);
			this->tabPage3->Controls->Add(this->label78);
			this->tabPage3->Controls->Add(this->label27);
			this->tabPage3->Location = System::Drawing::Point(4, 40);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1182, 693);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"EMG";
			this->tabPage3->UseVisualStyleBackColor = true;
			this->tabPage3->Click += gcnew System::EventHandler(this, &MyForm::tabPage3_Click);
			this->tabPage3->Enter += gcnew System::EventHandler(this, &MyForm::tabPage3_Enter);
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(844, 175);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(54, 13);
			this->label68->TabIndex = 141;
			this->label68->Text = L"Threshold";
			// 
			// numericUpDown5
			// 
			this->numericUpDown5->Location = System::Drawing::Point(904, 172);
			this->numericUpDown5->Name = L"numericUpDown5";
			this->numericUpDown5->Size = System::Drawing::Size(120, 20);
			this->numericUpDown5->TabIndex = 140;
			this->numericUpDown5->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numericUpDown5->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown5_ValueChanged);
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(395, 172);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(136, 17);
			this->checkBox7->TabIndex = 139;
			this->checkBox7->Text = L"Normalize MAV, WAVE";
			this->checkBox7->UseVisualStyleBackColor = true;
			this->checkBox7->CheckStateChanged += gcnew System::EventHandler(this, &MyForm::checkBox7_CheckStateChanged);
			// 
			// chart3
			// 
			this->chart3->BorderlineColor = System::Drawing::Color::Black;
			this->chart3->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			this->chart3->Location = System::Drawing::Point(6, 195);
			this->chart3->Name = L"chart3";
			this->chart3->Size = System::Drawing::Size(383, 370);
			this->chart3->TabIndex = 138;
			this->chart3->Text = L"chart3";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(833, 601);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(46, 13);
			this->label67->TabIndex = 137;
			this->label67->Text = L"Data #2";
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(441, 601);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(46, 13);
			this->label65->TabIndex = 137;
			this->label65->Text = L"Data #2";
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(833, 574);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(46, 13);
			this->label66->TabIndex = 137;
			this->label66->Text = L"Data #1";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(441, 574);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(46, 13);
			this->label54->TabIndex = 137;
			this->label54->Text = L"Data #1";
			// 
			// comboBox7
			// 
			this->comboBox7->FormattingEnabled = true;
			this->comboBox7->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"WAVE", L"MAV", L"ZERO", L"TURN" });
			this->comboBox7->Location = System::Drawing::Point(885, 571);
			this->comboBox7->Name = L"comboBox7";
			this->comboBox7->Size = System::Drawing::Size(126, 21);
			this->comboBox7->TabIndex = 136;
			this->comboBox7->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox7_SelectionChangeCommitted);
			// 
			// comboBox9
			// 
			this->comboBox9->FormattingEnabled = true;
			this->comboBox9->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"WAVE", L"MAV", L"ZERO", L"TURN" });
			this->comboBox9->Location = System::Drawing::Point(885, 598);
			this->comboBox9->Name = L"comboBox9";
			this->comboBox9->Size = System::Drawing::Size(126, 21);
			this->comboBox9->TabIndex = 136;
			this->comboBox9->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox9_SelectedIndexChanged);
			// 
			// comboBox8
			// 
			this->comboBox8->FormattingEnabled = true;
			this->comboBox8->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"WAVE", L"MAV", L"ZERO", L"TURN" });
			this->comboBox8->Location = System::Drawing::Point(493, 598);
			this->comboBox8->Name = L"comboBox8";
			this->comboBox8->Size = System::Drawing::Size(147, 21);
			this->comboBox8->TabIndex = 136;
			this->comboBox8->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox8_SelectionChangeCommitted);
			// 
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"WAVE", L"MAV", L"ZERO", L"TURN" });
			this->comboBox6->Location = System::Drawing::Point(493, 571);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(147, 21);
			this->comboBox6->TabIndex = 136;
			this->comboBox6->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox6_SelectionChangeCommitted);
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(210, 37);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 128, 0, 0, 0 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(93, 20);
			this->numericUpDown3->TabIndex = 135;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 40, 0, 0, 0 });
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(76, 38);
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(93, 20);
			this->numericUpDown2->TabIndex = 134;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
			// 
			// chart2
			// 
			this->chart2->BackColor = System::Drawing::Color::Transparent;
			this->chart2->BorderlineColor = System::Drawing::Color::Black;
			this->chart2->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			this->chart2->Location = System::Drawing::Point(771, 195);
			this->chart2->Name = L"chart2";
			this->chart2->Size = System::Drawing::Size(370, 370);
			this->chart2->TabIndex = 132;
			this->chart2->Text = L"chart2";
			// 
			// chart1
			// 
			this->chart1->BackColor = System::Drawing::Color::Transparent;
			this->chart1->BorderlineColor = System::Drawing::Color::Black;
			this->chart1->BorderlineDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			this->chart1->BorderSkin->BorderDashStyle = System::Windows::Forms::DataVisualization::Charting::ChartDashStyle::Dash;
			this->chart1->Location = System::Drawing::Point(395, 195);
			this->chart1->Name = L"chart1";
			this->chart1->Size = System::Drawing::Size(370, 370);
			this->chart1->TabIndex = 131;
			this->chart1->Text = L"chart2";
			// 
			// button30
			// 
			this->button30->Location = System::Drawing::Point(949, 38);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(75, 23);
			this->button30->TabIndex = 128;
			this->button30->Text = L"Pause";
			this->button30->UseVisualStyleBackColor = true;
			this->button30->Click += gcnew System::EventHandler(this, &MyForm::button30_Click);
			// 
			// button31
			// 
			this->button31->Location = System::Drawing::Point(868, 38);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(75, 23);
			this->button31->TabIndex = 129;
			this->button31->Text = L"Play";
			this->button31->UseVisualStyleBackColor = true;
			this->button31->Click += gcnew System::EventHandler(this, &MyForm::button31_Click);
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->textBox54);
			this->groupBox11->Controls->Add(this->label148);
			this->groupBox11->Controls->Add(this->textBox53);
			this->groupBox11->Controls->Add(this->textBox52);
			this->groupBox11->Controls->Add(this->textBox15);
			this->groupBox11->Controls->Add(this->label147);
			this->groupBox11->Controls->Add(this->textBox51);
			this->groupBox11->Controls->Add(this->textBox50);
			this->groupBox11->Controls->Add(this->label137);
			this->groupBox11->Controls->Add(this->label146);
			this->groupBox11->Controls->Add(this->label138);
			this->groupBox11->Controls->Add(this->label144);
			this->groupBox11->Controls->Add(this->label141);
			this->groupBox11->Controls->Add(this->textBox49);
			this->groupBox11->Controls->Add(this->label142);
			this->groupBox11->Controls->Add(this->textBox48);
			this->groupBox11->Location = System::Drawing::Point(76, 63);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(942, 92);
			this->groupBox11->TabIndex = 127;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Raw EMG";
			// 
			// textBox54
			// 
			this->textBox54->Location = System::Drawing::Point(50, 49);
			this->textBox54->Name = L"textBox54";
			this->textBox54->ReadOnly = true;
			this->textBox54->Size = System::Drawing::Size(100, 20);
			this->textBox54->TabIndex = 13;
			// 
			// label148
			// 
			this->label148->AutoSize = true;
			this->label148->Location = System::Drawing::Point(71, 33);
			this->label148->Name = L"label148";
			this->label148->Size = System::Drawing::Size(62, 13);
			this->label148->TabIndex = 24;
			this->label148->Text = L"Channel #1";
			// 
			// textBox53
			// 
			this->textBox53->Location = System::Drawing::Point(474, 49);
			this->textBox53->Name = L"textBox53";
			this->textBox53->ReadOnly = true;
			this->textBox53->Size = System::Drawing::Size(100, 20);
			this->textBox53->TabIndex = 14;
			// 
			// textBox52
			// 
			this->textBox52->Location = System::Drawing::Point(262, 49);
			this->textBox52->Name = L"textBox52";
			this->textBox52->ReadOnly = true;
			this->textBox52->Size = System::Drawing::Size(100, 20);
			this->textBox52->TabIndex = 15;
			// 
			// textBox15
			// 
			this->textBox15->Location = System::Drawing::Point(580, 49);
			this->textBox15->Name = L"textBox15";
			this->textBox15->ReadOnly = true;
			this->textBox15->Size = System::Drawing::Size(100, 20);
			this->textBox15->TabIndex = 14;
			// 
			// label147
			// 
			this->label147->AutoSize = true;
			this->label147->Location = System::Drawing::Point(496, 33);
			this->label147->Name = L"label147";
			this->label147->Size = System::Drawing::Size(62, 13);
			this->label147->TabIndex = 27;
			this->label147->Text = L"Channel #5";
			// 
			// textBox51
			// 
			this->textBox51->Location = System::Drawing::Point(156, 49);
			this->textBox51->Name = L"textBox51";
			this->textBox51->ReadOnly = true;
			this->textBox51->Size = System::Drawing::Size(100, 20);
			this->textBox51->TabIndex = 16;
			// 
			// textBox50
			// 
			this->textBox50->Location = System::Drawing::Point(686, 49);
			this->textBox50->Name = L"textBox50";
			this->textBox50->ReadOnly = true;
			this->textBox50->Size = System::Drawing::Size(100, 20);
			this->textBox50->TabIndex = 17;
			// 
			// label137
			// 
			this->label137->AutoSize = true;
			this->label137->Location = System::Drawing::Point(810, 33);
			this->label137->Name = L"label137";
			this->label137->Size = System::Drawing::Size(62, 13);
			this->label137->TabIndex = 20;
			this->label137->Text = L"Channel #8";
			// 
			// label146
			// 
			this->label146->AutoSize = true;
			this->label146->Location = System::Drawing::Point(281, 33);
			this->label146->Name = L"label146";
			this->label146->Size = System::Drawing::Size(62, 13);
			this->label146->TabIndex = 26;
			this->label146->Text = L"Channel #3";
			// 
			// label138
			// 
			this->label138->AutoSize = true;
			this->label138->Location = System::Drawing::Point(389, 33);
			this->label138->Name = L"label138";
			this->label138->Size = System::Drawing::Size(62, 13);
			this->label138->TabIndex = 21;
			this->label138->Text = L"Channel #4";
			// 
			// label144
			// 
			this->label144->AutoSize = true;
			this->label144->Location = System::Drawing::Point(704, 33);
			this->label144->Name = L"label144";
			this->label144->Size = System::Drawing::Size(62, 13);
			this->label144->TabIndex = 25;
			this->label144->Text = L"Channel #7";
			// 
			// label141
			// 
			this->label141->AutoSize = true;
			this->label141->Location = System::Drawing::Point(599, 33);
			this->label141->Name = L"label141";
			this->label141->Size = System::Drawing::Size(62, 13);
			this->label141->TabIndex = 22;
			this->label141->Text = L"Channel #6";
			// 
			// textBox49
			// 
			this->textBox49->Location = System::Drawing::Point(368, 49);
			this->textBox49->Name = L"textBox49";
			this->textBox49->ReadOnly = true;
			this->textBox49->Size = System::Drawing::Size(100, 20);
			this->textBox49->TabIndex = 19;
			// 
			// label142
			// 
			this->label142->AutoSize = true;
			this->label142->Location = System::Drawing::Point(173, 33);
			this->label142->Name = L"label142";
			this->label142->Size = System::Drawing::Size(62, 13);
			this->label142->TabIndex = 23;
			this->label142->Text = L"Channel #2";
			// 
			// textBox48
			// 
			this->textBox48->Location = System::Drawing::Point(792, 49);
			this->textBox48->Name = L"textBox48";
			this->textBox48->ReadOnly = true;
			this->textBox48->Size = System::Drawing::Size(100, 20);
			this->textBox48->TabIndex = 18;
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->Location = System::Drawing::Point(73, 21);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(96, 13);
			this->label78->TabIndex = 12;
			this->label78->Text = L"Window Increment";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(207, 21);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(82, 13);
			this->label27->TabIndex = 9;
			this->label27->Text = L"Window Length";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->groupBox6);
			this->tabPage2->Controls->Add(this->groupBox12);
			this->tabPage2->Controls->Add(this->comboBox3);
			this->tabPage2->Controls->Add(this->button29);
			this->tabPage2->Controls->Add(this->button28);
			this->tabPage2->Controls->Add(this->groupBox10);
			this->tabPage2->Location = System::Drawing::Point(4, 40);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1182, 693);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"IMU";
			this->tabPage2->UseVisualStyleBackColor = true;
			this->tabPage2->Enter += gcnew System::EventHandler(this, &MyForm::tabPage2_Enter);
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->label58);
			this->groupBox6->Controls->Add(this->label64);
			this->groupBox6->Controls->Add(this->label63);
			this->groupBox6->Controls->Add(this->label61);
			this->groupBox6->Controls->Add(this->label62);
			this->groupBox6->Controls->Add(this->label60);
			this->groupBox6->Controls->Add(this->label59);
			this->groupBox6->Controls->Add(this->label55);
			this->groupBox6->Controls->Add(this->label57);
			this->groupBox6->Controls->Add(this->label56);
			this->groupBox6->Controls->Add(this->label28);
			this->groupBox6->Controls->Add(this->label23);
			this->groupBox6->Controls->Add(this->comboBox5);
			this->groupBox6->Controls->Add(this->comboBox4);
			this->groupBox6->Controls->Add(this->chart5);
			this->groupBox6->Controls->Add(this->chart6);
			this->groupBox6->Location = System::Drawing::Point(294, 110);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(743, 419);
			this->groupBox6->TabIndex = 11;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Graphs";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->ForeColor = System::Drawing::Color::Red;
			this->label58->Location = System::Drawing::Point(380, 292);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(31, 13);
			this->label58->TabIndex = 38;
			this->label58->Text = L"Pitch";
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->ForeColor = System::Drawing::Color::Blue;
			this->label64->Location = System::Drawing::Point(640, 374);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(28, 13);
			this->label64->TabIndex = 38;
			this->label64->Text = L"Yaw";
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->ForeColor = System::Drawing::Color::Lime;
			this->label63->Location = System::Drawing::Point(546, 374);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(31, 13);
			this->label63->TabIndex = 38;
			this->label63->Text = L"Pitch";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->ForeColor = System::Drawing::Color::Blue;
			this->label61->Location = System::Drawing::Point(284, 374);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(28, 13);
			this->label61->TabIndex = 38;
			this->label61->Text = L"Yaw";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->ForeColor = System::Drawing::Color::Red;
			this->label62->Location = System::Drawing::Point(450, 374);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(25, 13);
			this->label62->TabIndex = 38;
			this->label62->Text = L"Roll";
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->ForeColor = System::Drawing::Color::Lime;
			this->label60->Location = System::Drawing::Point(190, 374);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(31, 13);
			this->label60->TabIndex = 38;
			this->label60->Text = L"Pitch";
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->ForeColor = System::Drawing::Color::Red;
			this->label59->Location = System::Drawing::Point(94, 374);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(25, 13);
			this->label59->TabIndex = 38;
			this->label59->Text = L"Roll";
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->ForeColor = System::Drawing::Color::Red;
			this->label55->Location = System::Drawing::Point(32, 292);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(31, 13);
			this->label55->TabIndex = 38;
			this->label55->Text = L"Pitch";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->ForeColor = System::Drawing::Color::Lime;
			this->label57->Location = System::Drawing::Point(380, 207);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(28, 13);
			this->label57->TabIndex = 38;
			this->label57->Text = L"Yaw";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->ForeColor = System::Drawing::Color::Blue;
			this->label56->Location = System::Drawing::Point(380, 111);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(25, 13);
			this->label56->TabIndex = 38;
			this->label56->Text = L"Roll";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->ForeColor = System::Drawing::Color::Lime;
			this->label28->Location = System::Drawing::Point(32, 207);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(28, 13);
			this->label28->TabIndex = 38;
			this->label28->Text = L"Yaw";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->ForeColor = System::Drawing::Color::Blue;
			this->label23->Location = System::Drawing::Point(32, 111);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(25, 13);
			this->label23->TabIndex = 38;
			this->label23->Text = L"Roll";
			// 
			// comboBox5
			// 
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"1 Ori", L"1 Gyr", L"1 Acc", L"2 Ori", L"2 Gyr",
					L"2 Acc"
			});
			this->comboBox5->Location = System::Drawing::Point(411, 20);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(111, 21);
			this->comboBox5->TabIndex = 37;
			this->comboBox5->Text = L"Select Graph...";
			this->comboBox5->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox5_SelectionChangeCommitted);
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"1 Ori", L"1 Gyr", L"1 Acc", L"2 Ori", L"2 Gyr",
					L"2 Acc"
			});
			this->comboBox4->Location = System::Drawing::Point(63, 20);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(111, 21);
			this->comboBox4->TabIndex = 37;
			this->comboBox4->Text = L"Select Graph...";
			this->comboBox4->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::comboBox4_SelectionChangeCommitted);
			// 
			// chart5
			// 
			this->chart5->BackColor = System::Drawing::Color::WhiteSmoke;
			this->chart5->Location = System::Drawing::Point(411, 64);
			this->chart5->Name = L"chart5";
			this->chart5->Size = System::Drawing::Size(300, 300);
			this->chart5->TabIndex = 36;
			this->chart5->Text = L"chart6";
			// 
			// chart6
			// 
			this->chart6->BackColor = System::Drawing::Color::WhiteSmoke;
			this->chart6->Location = System::Drawing::Point(63, 64);
			this->chart6->Name = L"chart6";
			this->chart6->Size = System::Drawing::Size(300, 300);
			this->chart6->TabIndex = 36;
			this->chart6->Text = L"chart6";
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->groupBox13);
			this->groupBox12->Controls->Add(this->groupBox14);
			this->groupBox12->Controls->Add(this->groupBox15);
			this->groupBox12->Location = System::Drawing::Point(22, 165);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(242, 332);
			this->groupBox12->TabIndex = 8;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Myo #2";
			this->groupBox12->Visible = false;
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->label24);
			this->groupBox13->Controls->Add(this->label25);
			this->groupBox13->Controls->Add(this->label26);
			this->groupBox13->Controls->Add(this->label33);
			this->groupBox13->Controls->Add(this->textBox17);
			this->groupBox13->Controls->Add(this->label34);
			this->groupBox13->Controls->Add(this->textBox21);
			this->groupBox13->Controls->Add(this->label35);
			this->groupBox13->Controls->Add(this->textBox23);
			this->groupBox13->Location = System::Drawing::Point(8, 12);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(226, 100);
			this->groupBox13->TabIndex = 0;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"Orientation";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(153, 75);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(47, 13);
			this->label24->TabIndex = 8;
			this->label24->Text = L"Degrees";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(153, 47);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(47, 13);
			this->label25->TabIndex = 7;
			this->label25->Text = L"Degrees";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(153, 19);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(47, 13);
			this->label26->TabIndex = 6;
			this->label26->Text = L"Degrees";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(7, 75);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(28, 13);
			this->label33->TabIndex = 5;
			this->label33->Text = L"Yaw";
			// 
			// textBox17
			// 
			this->textBox17->Location = System::Drawing::Point(50, 72);
			this->textBox17->Name = L"textBox17";
			this->textBox17->ReadOnly = true;
			this->textBox17->Size = System::Drawing::Size(100, 20);
			this->textBox17->TabIndex = 4;
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(7, 47);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(31, 13);
			this->label34->TabIndex = 3;
			this->label34->Text = L"Pitch";
			// 
			// textBox21
			// 
			this->textBox21->Location = System::Drawing::Point(50, 44);
			this->textBox21->Name = L"textBox21";
			this->textBox21->ReadOnly = true;
			this->textBox21->Size = System::Drawing::Size(100, 20);
			this->textBox21->TabIndex = 2;
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(7, 19);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(25, 13);
			this->label35->TabIndex = 1;
			this->label35->Text = L"Roll";
			// 
			// textBox23
			// 
			this->textBox23->Location = System::Drawing::Point(50, 16);
			this->textBox23->Name = L"textBox23";
			this->textBox23->ReadOnly = true;
			this->textBox23->Size = System::Drawing::Size(100, 20);
			this->textBox23->TabIndex = 0;
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->label36);
			this->groupBox14->Controls->Add(this->label37);
			this->groupBox14->Controls->Add(this->label38);
			this->groupBox14->Controls->Add(this->label41);
			this->groupBox14->Controls->Add(this->textBox24);
			this->groupBox14->Controls->Add(this->textBox25);
			this->groupBox14->Controls->Add(this->label42);
			this->groupBox14->Controls->Add(this->label43);
			this->groupBox14->Controls->Add(this->textBox26);
			this->groupBox14->Location = System::Drawing::Point(8, 224);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(226, 100);
			this->groupBox14->TabIndex = 1;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Gyroscope";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(157, 72);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(37, 13);
			this->label36->TabIndex = 20;
			this->label36->Text = L"Deg/s";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(157, 44);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(37, 13);
			this->label37->TabIndex = 19;
			this->label37->Text = L"Deg/s";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(157, 16);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(37, 13);
			this->label38->TabIndex = 18;
			this->label38->Text = L"Deg/s";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(9, 72);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(14, 13);
			this->label41->TabIndex = 17;
			this->label41->Text = L"Z";
			// 
			// textBox24
			// 
			this->textBox24->Location = System::Drawing::Point(52, 13);
			this->textBox24->Name = L"textBox24";
			this->textBox24->ReadOnly = true;
			this->textBox24->Size = System::Drawing::Size(100, 20);
			this->textBox24->TabIndex = 12;
			// 
			// textBox25
			// 
			this->textBox25->Location = System::Drawing::Point(52, 41);
			this->textBox25->Name = L"textBox25";
			this->textBox25->ReadOnly = true;
			this->textBox25->Size = System::Drawing::Size(100, 20);
			this->textBox25->TabIndex = 14;
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(9, 16);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(14, 13);
			this->label42->TabIndex = 13;
			this->label42->Text = L"X";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(9, 44);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(14, 13);
			this->label43->TabIndex = 15;
			this->label43->Text = L"Y";
			// 
			// textBox26
			// 
			this->textBox26->Location = System::Drawing::Point(52, 69);
			this->textBox26->Name = L"textBox26";
			this->textBox26->ReadOnly = true;
			this->textBox26->Size = System::Drawing::Size(100, 20);
			this->textBox26->TabIndex = 16;
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->label44);
			this->groupBox15->Controls->Add(this->label45);
			this->groupBox15->Controls->Add(this->label46);
			this->groupBox15->Controls->Add(this->label47);
			this->groupBox15->Controls->Add(this->label48);
			this->groupBox15->Controls->Add(this->textBox27);
			this->groupBox15->Controls->Add(this->textBox28);
			this->groupBox15->Controls->Add(this->label49);
			this->groupBox15->Controls->Add(this->textBox32);
			this->groupBox15->Location = System::Drawing::Point(8, 118);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(226, 100);
			this->groupBox15->TabIndex = 1;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"Accelerometer";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(153, 72);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(20, 13);
			this->label44->TabIndex = 14;
			this->label44->Text = L"g\'s";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(153, 44);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(20, 13);
			this->label45->TabIndex = 13;
			this->label45->Text = L"g\'s";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(153, 16);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(20, 13);
			this->label46->TabIndex = 12;
			this->label46->Text = L"g\'s";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(6, 72);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(14, 13);
			this->label47->TabIndex = 11;
			this->label47->Text = L"Z";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(6, 16);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(14, 13);
			this->label48->TabIndex = 7;
			this->label48->Text = L"X";
			// 
			// textBox27
			// 
			this->textBox27->Location = System::Drawing::Point(49, 69);
			this->textBox27->Name = L"textBox27";
			this->textBox27->ReadOnly = true;
			this->textBox27->Size = System::Drawing::Size(100, 20);
			this->textBox27->TabIndex = 10;
			// 
			// textBox28
			// 
			this->textBox28->Location = System::Drawing::Point(49, 13);
			this->textBox28->Name = L"textBox28";
			this->textBox28->ReadOnly = true;
			this->textBox28->Size = System::Drawing::Size(100, 20);
			this->textBox28->TabIndex = 6;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(6, 44);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(14, 13);
			this->label49->TabIndex = 9;
			this->label49->Text = L"Y";
			// 
			// textBox32
			// 
			this->textBox32->Location = System::Drawing::Point(49, 41);
			this->textBox32->Name = L"textBox32";
			this->textBox32->ReadOnly = true;
			this->textBox32->Size = System::Drawing::Size(100, 20);
			this->textBox32->TabIndex = 8;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Myo #1", L"Myo #2" });
			this->comboBox3->Location = System::Drawing::Point(143, 138);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 21);
			this->comboBox3->TabIndex = 10;
			this->comboBox3->Text = L"Select Myo...";
			this->comboBox3->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox3_SelectedIndexChanged_1);
			// 
			// button29
			// 
			this->button29->Location = System::Drawing::Point(877, 6);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(75, 23);
			this->button29->TabIndex = 9;
			this->button29->Text = L"Pause";
			this->button29->UseVisualStyleBackColor = true;
			this->button29->Click += gcnew System::EventHandler(this, &MyForm::button29_Click);
			// 
			// button28
			// 
			this->button28->Location = System::Drawing::Point(796, 6);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(75, 23);
			this->button28->TabIndex = 9;
			this->button28->Text = L"Resume";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &MyForm::button28_Click);
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->groupBox3);
			this->groupBox10->Controls->Add(this->groupBox2);
			this->groupBox10->Controls->Add(this->groupBox1);
			this->groupBox10->Location = System::Drawing::Point(22, 165);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(242, 332);
			this->groupBox10->TabIndex = 7;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Myo #1";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label19);
			this->groupBox3->Controls->Add(this->label18);
			this->groupBox3->Controls->Add(this->label17);
			this->groupBox3->Controls->Add(this->label11);
			this->groupBox3->Controls->Add(this->textBox12);
			this->groupBox3->Controls->Add(this->textBox13);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->label13);
			this->groupBox3->Controls->Add(this->textBox11);
			this->groupBox3->Location = System::Drawing::Point(8, 224);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(226, 100);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Gyroscope";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(157, 72);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(37, 13);
			this->label19->TabIndex = 20;
			this->label19->Text = L"Deg/s";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(157, 44);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(37, 13);
			this->label18->TabIndex = 19;
			this->label18->Text = L"Deg/s";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(157, 16);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(37, 13);
			this->label17->TabIndex = 18;
			this->label17->Text = L"Deg/s";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(9, 72);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(14, 13);
			this->label11->TabIndex = 17;
			this->label11->Text = L"Z";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(52, 13);
			this->textBox12->Name = L"textBox12";
			this->textBox12->ReadOnly = true;
			this->textBox12->Size = System::Drawing::Size(100, 20);
			this->textBox12->TabIndex = 12;
			// 
			// textBox13
			// 
			this->textBox13->Location = System::Drawing::Point(52, 41);
			this->textBox13->Name = L"textBox13";
			this->textBox13->ReadOnly = true;
			this->textBox13->Size = System::Drawing::Size(100, 20);
			this->textBox13->TabIndex = 14;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(9, 16);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(14, 13);
			this->label12->TabIndex = 13;
			this->label12->Text = L"X";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(9, 44);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(14, 13);
			this->label13->TabIndex = 15;
			this->label13->Text = L"Y";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(52, 69);
			this->textBox11->Name = L"textBox11";
			this->textBox11->ReadOnly = true;
			this->textBox11->Size = System::Drawing::Size(100, 20);
			this->textBox11->TabIndex = 16;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->textBox5);
			this->groupBox2->Controls->Add(this->textBox7);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->textBox6);
			this->groupBox2->Location = System::Drawing::Point(8, 118);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(226, 100);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Accelerometer";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &MyForm::groupBox2_Enter);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(153, 72);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(20, 13);
			this->label16->TabIndex = 14;
			this->label16->Text = L"g\'s";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(153, 44);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(20, 13);
			this->label15->TabIndex = 13;
			this->label15->Text = L"g\'s";
			this->label15->Click += gcnew System::EventHandler(this, &MyForm::label15_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(153, 16);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(20, 13);
			this->label14->TabIndex = 12;
			this->label14->Text = L"g\'s";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 72);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(14, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Z";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 16);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(14, 13);
			this->label7->TabIndex = 7;
			this->label7->Text = L"X";
			this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(49, 69);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 10;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(49, 13);
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 6;
			this->textBox7->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox7_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 44);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(14, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Y";
			this->label6->Click += gcnew System::EventHandler(this, &MyForm::label6_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(49, 41);
			this->textBox6->Name = L"textBox6";
			this->textBox6->ReadOnly = true;
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 8;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox6_TextChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->textBox4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->textBox3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Location = System::Drawing::Point(8, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(226, 100);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Orientation";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(153, 75);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(47, 13);
			this->label10->TabIndex = 8;
			this->label10->Text = L"Degrees";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(153, 47);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(47, 13);
			this->label9->TabIndex = 7;
			this->label9->Text = L"Degrees";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(153, 19);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(47, 13);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Degrees";
			this->label8->Click += gcnew System::EventHandler(this, &MyForm::label8_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 75);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Yaw";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(50, 72);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 47);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Pitch";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(50, 44);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Roll";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(50, 16);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->textBox34);
			this->tabPage1->Controls->Add(this->textBox33);
			this->tabPage1->Controls->Add(this->label51);
			this->tabPage1->Controls->Add(this->label50);
			this->tabPage1->Controls->Add(this->groupBox8);
			this->tabPage1->Controls->Add(this->groupBox7);
			this->tabPage1->Controls->Add(this->groupBox5);
			this->tabPage1->Location = System::Drawing::Point(4, 40);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1182, 693);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Input";
			this->tabPage1->UseVisualStyleBackColor = true;
			this->tabPage1->Enter += gcnew System::EventHandler(this, &MyForm::tabPage1_Enter);
			// 
			// textBox34
			// 
			this->textBox34->Location = System::Drawing::Point(477, 25);
			this->textBox34->Name = L"textBox34";
			this->textBox34->ReadOnly = true;
			this->textBox34->Size = System::Drawing::Size(133, 20);
			this->textBox34->TabIndex = 14;
			// 
			// textBox33
			// 
			this->textBox33->Location = System::Drawing::Point(289, 25);
			this->textBox33->Name = L"textBox33";
			this->textBox33->ReadOnly = true;
			this->textBox33->Size = System::Drawing::Size(133, 20);
			this->textBox33->TabIndex = 12;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(431, 28);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(40, 13);
			this->label51->TabIndex = 13;
			this->label51->Text = L"Status:";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(203, 28);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(80, 13);
			this->label50->TabIndex = 11;
			this->label50->Text = L"Streaming from:";
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label39);
			this->groupBox8->Controls->Add(this->progressBar1);
			this->groupBox8->Controls->Add(this->button23);
			this->groupBox8->Controls->Add(this->checkBox6);
			this->groupBox8->Controls->Add(this->button13);
			this->groupBox8->Controls->Add(this->label30);
			this->groupBox8->Controls->Add(this->textBox16);
			this->groupBox8->Controls->Add(this->textBox19);
			this->groupBox8->Controls->Add(this->button18);
			this->groupBox8->Location = System::Drawing::Point(33, 340);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(450, 198);
			this->groupBox8->TabIndex = 10;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Playback";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->BackColor = System::Drawing::Color::Transparent;
			this->label39->Location = System::Drawing::Point(347, 124);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(21, 13);
			this->label39->TabIndex = 11;
			this->label39->Text = L"0%";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(57, 119);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(284, 23);
			this->progressBar1->TabIndex = 10;
			// 
			// button23
			// 
			this->button23->Location = System::Drawing::Point(57, 66);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(121, 23);
			this->button23->TabIndex = 9;
			this->button23->Text = L"Load IMU File";
			this->button23->UseVisualStyleBackColor = true;
			this->button23->Click += gcnew System::EventHandler(this, &MyForm::button23_Click);
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(197, 153);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(76, 17);
			this->checkBox6->TabIndex = 8;
			this->checkBox6->Text = L"Loop Data";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(57, 35);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(121, 25);
			this->button13->TabIndex = 5;
			this->button13->Text = L"Load EMG File";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MyForm::button13_Click);
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(243, 22);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(62, 13);
			this->label30->TabIndex = 1;
			this->label30->Text = L"Loaded File";
			// 
			// textBox16
			// 
			this->textBox16->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox16->Enabled = false;
			this->textBox16->Location = System::Drawing::Point(197, 64);
			this->textBox16->Name = L"textBox16";
			this->textBox16->ReadOnly = true;
			this->textBox16->Size = System::Drawing::Size(144, 20);
			this->textBox16->TabIndex = 7;
			// 
			// textBox19
			// 
			this->textBox19->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox19->Enabled = false;
			this->textBox19->Location = System::Drawing::Point(197, 38);
			this->textBox19->Name = L"textBox19";
			this->textBox19->ReadOnly = true;
			this->textBox19->Size = System::Drawing::Size(144, 20);
			this->textBox19->TabIndex = 7;
			// 
			// button18
			// 
			this->button18->Enabled = false;
			this->button18->Location = System::Drawing::Point(57, 148);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(121, 25);
			this->button18->TabIndex = 6;
			this->button18->Text = L"Play File";
			this->button18->UseVisualStyleBackColor = true;
			this->button18->Click += gcnew System::EventHandler(this, &MyForm::button18_Click);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->button22);
			this->groupBox7->Controls->Add(this->groupBox4);
			this->groupBox7->Controls->Add(this->button20);
			this->groupBox7->Controls->Add(this->label31);
			this->groupBox7->Controls->Add(this->textBox20);
			this->groupBox7->Controls->Add(this->button2);
			this->groupBox7->Controls->Add(this->label29);
			this->groupBox7->Controls->Add(this->textBox18);
			this->groupBox7->Controls->Add(this->button3);
			this->groupBox7->Location = System::Drawing::Point(498, 340);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(450, 198);
			this->groupBox7->TabIndex = 9;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Recording";
			// 
			// button22
			// 
			this->button22->Location = System::Drawing::Point(243, 38);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(25, 20);
			this->button22->TabIndex = 14;
			this->button22->Text = L"...";
			this->button22->UseVisualStyleBackColor = true;
			this->button22->Click += gcnew System::EventHandler(this, &MyForm::button22_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->checkBox9);
			this->groupBox4->Controls->Add(this->checkBox8);
			this->groupBox4->Location = System::Drawing::Point(26, 110);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(130, 62);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Record Selection";
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(13, 38);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(46, 17);
			this->checkBox9->TabIndex = 0;
			this->checkBox9->Text = L"IMU";
			this->checkBox9->UseVisualStyleBackColor = true;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(13, 20);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(50, 17);
			this->checkBox8->TabIndex = 0;
			this->checkBox8->Text = L"EMG";
			this->checkBox8->UseVisualStyleBackColor = true;
			// 
			// button20
			// 
			this->button20->Enabled = false;
			this->button20->Location = System::Drawing::Point(299, 73);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(121, 25);
			this->button20->TabIndex = 10;
			this->button20->Text = L"Place Marker";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &MyForm::button20_Click);
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(23, 42);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(57, 13);
			this->label31->TabIndex = 9;
			this->label31->Text = L"File Name:";
			// 
			// textBox20
			// 
			this->textBox20->Enabled = false;
			this->textBox20->Location = System::Drawing::Point(124, 39);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(113, 20);
			this->textBox20->TabIndex = 8;
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(299, 36);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(121, 25);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Record";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(23, 79);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(92, 13);
			this->label29->TabIndex = 1;
			this->label29->Text = L"Recording Status:";
			// 
			// textBox18
			// 
			this->textBox18->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox18->Enabled = false;
			this->textBox18->Location = System::Drawing::Point(124, 76);
			this->textBox18->Name = L"textBox18";
			this->textBox18->ReadOnly = true;
			this->textBox18->Size = System::Drawing::Size(144, 20);
			this->textBox18->TabIndex = 7;
			this->textBox18->Text = L"Not Recording";
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(299, 110);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(121, 25);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Stop Recording";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click_1);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button32);
			this->groupBox5->Controls->Add(this->groupBox16);
			this->groupBox5->Controls->Add(this->button25);
			this->groupBox5->Controls->Add(this->groupBox9);
			this->groupBox5->Controls->Add(this->button24);
			this->groupBox5->Location = System::Drawing::Point(33, 51);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(915, 283);
			this->groupBox5->TabIndex = 8;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Myo Connections";
			// 
			// button32
			// 
			this->button32->Location = System::Drawing::Point(658, 202);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(227, 38);
			this->button32->TabIndex = 11;
			this->button32->Text = L"Chart";
			this->button32->UseVisualStyleBackColor = true;
			this->button32->Click += gcnew System::EventHandler(this, &MyForm::button32_Click);
			// 
			// groupBox16
			// 
			this->groupBox16->Controls->Add(this->button26);
			this->groupBox16->Controls->Add(this->label52);
			this->groupBox16->Controls->Add(this->progressBar2);
			this->groupBox16->Controls->Add(this->buttonConnect1);
			this->groupBox16->Controls->Add(this->textBox1);
			this->groupBox16->Controls->Add(this->label1);
			this->groupBox16->Location = System::Drawing::Point(63, 19);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(268, 244);
			this->groupBox16->TabIndex = 10;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Primary Myo";
			// 
			// button26
			// 
			this->button26->Location = System::Drawing::Point(96, 134);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(75, 23);
			this->button26->TabIndex = 5;
			this->button26->Text = L"Vibrate";
			this->button26->UseVisualStyleBackColor = true;
			this->button26->Click += gcnew System::EventHandler(this, &MyForm::button26_Click);
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(103, 165);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(56, 13);
			this->label52->TabIndex = 4;
			this->label52->Text = L"Battery #1";
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(22, 183);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(221, 23);
			this->progressBar2->TabIndex = 3;
			// 
			// buttonConnect1
			// 
			this->buttonConnect1->Location = System::Drawing::Point(21, 51);
			this->buttonConnect1->Name = L"buttonConnect1";
			this->buttonConnect1->Size = System::Drawing::Size(221, 71);
			this->buttonConnect1->TabIndex = 0;
			this->buttonConnect1->Text = L"Connect!";
			this->buttonConnect1->UseVisualStyleBackColor = true;
			this->buttonConnect1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(119, 20);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(123, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(18, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Connection Status:";
			// 
			// button25
			// 
			this->button25->Enabled = false;
			this->button25->Location = System::Drawing::Point(658, 135);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(227, 40);
			this->button25->TabIndex = 4;
			this->button25->Text = L"Stop Streaming";
			this->button25->UseVisualStyleBackColor = true;
			this->button25->Click += gcnew System::EventHandler(this, &MyForm::button25_Click);
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->button27);
			this->groupBox9->Controls->Add(this->label53);
			this->groupBox9->Controls->Add(this->progressBar3);
			this->groupBox9->Controls->Add(this->label32);
			this->groupBox9->Controls->Add(this->button21);
			this->groupBox9->Controls->Add(this->textBox22);
			this->groupBox9->Location = System::Drawing::Point(380, 19);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(268, 244);
			this->groupBox9->TabIndex = 9;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"Secondary Myo (IMU only)";
			// 
			// button27
			// 
			this->button27->Location = System::Drawing::Point(95, 133);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(75, 23);
			this->button27->TabIndex = 12;
			this->button27->Text = L"Vibrate";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &MyForm::button27_Click);
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(105, 165);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(56, 13);
			this->label53->TabIndex = 4;
			this->label53->Text = L"Battery #2";
			// 
			// progressBar3
			// 
			this->progressBar3->Location = System::Drawing::Point(28, 181);
			this->progressBar3->Name = L"progressBar3";
			this->progressBar3->Size = System::Drawing::Size(219, 23);
			this->progressBar3->TabIndex = 4;
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(23, 23);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(97, 13);
			this->label32->TabIndex = 1;
			this->label32->Text = L"Connection Status:";
			// 
			// button21
			// 
			this->button21->Enabled = false;
			this->button21->Location = System::Drawing::Point(28, 51);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(219, 71);
			this->button21->TabIndex = 11;
			this->button21->Text = L"Connect!";
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Click += gcnew System::EventHandler(this, &MyForm::button21_Click);
			// 
			// textBox22
			// 
			this->textBox22->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->textBox22->Enabled = false;
			this->textBox22->Location = System::Drawing::Point(124, 20);
			this->textBox22->Name = L"textBox22";
			this->textBox22->ReadOnly = true;
			this->textBox22->Size = System::Drawing::Size(123, 20);
			this->textBox22->TabIndex = 2;
			// 
			// button24
			// 
			this->button24->Enabled = false;
			this->button24->Location = System::Drawing::Point(658, 70);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(227, 40);
			this->button24->TabIndex = 3;
			this->button24->Text = L"Start Streaming";
			this->button24->UseVisualStyleBackColor = true;
			this->button24->Click += gcnew System::EventHandler(this, &MyForm::button24_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->HotTrack = true;
			this->tabControl1->ItemSize = System::Drawing::Size(140, 36);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(55, 5);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1190, 737);
			this->tabControl1->TabIndex = 1;
			// 
			// folderBrowserDialog2
			// 
			this->folderBrowserDialog2->SelectedPath = L"C:\\Users\\admin\\Desktop";
			// 
			// openFileDialog3
			// 
			this->openFileDialog3->FileName = L"openFileDialog3";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1252, 785);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MyForm";
			this->Text = L"Myo Gesture Classification Sheet Alpha";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->tabPage6->ResumeLayout(false);
			this->tabPage6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox19->ResumeLayout(false);
			this->groupBox19->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart7))->EndInit();
			this->groupBox18->ResumeLayout(false);
			this->groupBox18->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
			this->groupBox17->ResumeLayout(false);
			this->groupBox17->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart6))->EndInit();
			this->groupBox12->ResumeLayout(false);
			this->groupBox13->ResumeLayout(false);
			this->groupBox13->PerformLayout();
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		Application::DoEvents();
		timer1->Stop();

		
		endtimer1 = false;
		playbackLoop = false;
		
		textBox1->Text = "Attempting to find a Myo";
		Application::DoEvents();
		if (!deviceMyo.myo)
		{

			deviceMyo.connect();
			if (!deviceMyo.myo) {

				textBox1->Text = "Connection Failed";

			}
			else {

				deviceMyo.myo->requestBatteryLevel();
				deviceMyo.resume_listener();
				deviceMyo.resume_emg();

				checkBox8->Checked = true;
				checkBox9->Checked = true;

				button24->Enabled = true;
				button25->Enabled = true;

				textBox20->Enabled = true; //Enable recording
				button2->Enabled = true;

				deviceMyo.myo->vibrate(myo::Myo::vibrationShort);

				deviceMyo.collector.knownMyos.push_back(deviceMyo.myo); //db

				textBox1->Text = "Myo #" + deviceMyo.collector.identifyMyo(deviceMyo.myo) + " connected";

				progressBar2->Value = deviceMyo.collector.battery1;
				deviceMyo.resume_emg(); //db

				myoStreaming = true;

				button21->Enabled = true;

			
				
			}
		}
		
		if (!deviceMyo.myo2){
			textBox22->Text = "Connection Failed!";
		}
		else {
			

			//test20.collector2.knownMyos.push_back(test20.myo2); db
			
			deviceMyo.myo2->vibrate(myo::Myo::vibrationShort);
			textBox22->Text = "Myo #" + deviceMyo.collector.identifyMyo(deviceMyo.myo2) + " Connected";
			deviceMyo.myo2->requestBatteryLevel();
			progressBar3->Value = deviceMyo.collector.battery2;
			twoMyos = true;
			deviceMyo.collector.knownMyos.push_back(deviceMyo.myo2);
			textBox22->Text = "Myo #" + deviceMyo.collector.identifyMyo(deviceMyo.myo2) + " Connected";
			//timer1->Start(); db
	
			
			
			
			

		}
		if (!(!deviceMyo.myo && !deviceMyo.myo2)){
			timer1->Start(); 
		}
		

	}
		
	private: System::Void button24_Click(System::Object^  sender, System::EventArgs^  e) {
									
		myoStreaming = true;
		endtimer1 = false;

		timer1->Start();
		
	}

	 private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {

		 timer1->Stop();

		 endtimer1 = false;

		 deviceMyo.hub.addListener(&deviceMyo.collector);
	
		 textBox22->Text = "Attempting to find a Myo";
		 Application::DoEvents();

		 if (deviceMyo.myo2){

			 //test20.collector2.knownMyos.push_back(test20.myo2); db
			 textBox22->Text = "Myo #" + deviceMyo.collector.identifyMyo(deviceMyo.myo2) + " Connected";
			 deviceMyo.myo2->vibrate(myo::Myo::vibrationShort);
			 twoMyos = true;
			 timer1->Start();
			 deviceMyo.myo2->requestBatteryLevel();
			
		 }
		 else{
			 textBox22->Text = "Connection Failed";
			 
		 }
			
	}
	
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
	
	timer1->Stop();
	deviceMyo.hub.removeListener(&deviceMyo.collector);
	
	deviceMyo.hub.~Hub();
	Application::DoEvents();

}

private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) {
	
	textBox34->Text = "Paused";

	myoStreaming = false;

	endtimer1 = true;
			  
}
	
//	unused but necessary events
	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label15_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void tabPage3_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label20_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	}
	private: System::Void backgroundWorker1_DoWork_1(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void checkBox1_CheckedChanged_1(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label22_Click(System::Object^  sender, System::EventArgs^  e) {
}


private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
	if (button11->Text == "Start Predicting"){
		button11->Text = "Stop Predicting";
		//Start receiving code
	}
	else{
		button11->Text = "Start Predicting";
		//Stop receiving /predicting
	}
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	if (button6->Text == "Enable Myo Mouse Control"){
		button6->Text = "Disable Myo Mouse Control";
		//Start receiving code
	}
	else{
		button6->Text = "Enable Myo Mouse Control";
		//Stop receiving /predicting
	}
}
//	more events
private: System::Void tabPage4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox46_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox50_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox44_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox53_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox35_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox48_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

}

private: System::Void tabPage6_Click(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

	checkBox8->Enabled = false;
	checkBox9->Enabled = false;


	button20->Enabled = true;
	button2->Enabled = false;
	button3->Enabled = true;
	if (textBox20->Text == "")
	{
		
		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time

		textBox20->Text = "" + localTime->tm_hour + localTime->tm_min + localTime->tm_sec;
	}

	//if EMG is checked
	if (checkBox8->Checked){

		recordingFileName = folderBrowserDialog1 -> SelectedPath + "/" + textBox20 -> Text + ".EMG.csv"; 
		//may want to change folderbrowserdialog1->selectedpath to userRecordDirectory variable for check
		stdRecordEMGFileName = context.marshal_as<std::string>(recordingFileName);
		fileEMGRecord.open(stdRecordEMGFileName);
		fileEMGRecord << "MARKER, EMG1, EMG2, EMG3, EMG4, EMG5, EMG6, EMG7, EMG8 \n ,";

	}

	//if IMU is checked
	if (checkBox9->Checked){
		//see above note
		recordingFileName = folderBrowserDialog1->SelectedPath + "/" + textBox20 -> Text + ".IMU.csv";
		stdRecordIMUFileName = context.marshal_as<std::string>(recordingFileName);
		
		fileIMURecord.open(stdRecordIMUFileName);
		
		if (twoMyos){
			//prints out titles and first blank for marker
			fileIMURecord << "MARKER, ROLL_1, PITCH_1, YAW_1, ACCEL_X_1, ACCEL_Y_1, ACCEL_Z_1, GYRO_X_1, GYRO_Y_1, GYRO_Z_1, ROLL_2, PITCH_2, YAW_2, ACCEL_X_2, ACCEL_Y_2, ACCEL_Z_2, GYRO_X_2, GYRO_Y_2, GYRO_Z_2 \n ,";

		}
		else {

			fileIMURecord << "MARKER, ROLL, PITCH, YAW, ACCEL_X, ACCEL_Y, ACCEL_Z, GYRO_X, GYRO_Y, GYRO_Z\n ,";

		}
		
	}
	record = true;
	textBox18->Text = "0:00";
	textBox20->ReadOnly = true;
	RecordTimer->Start();

}
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) {

	checkBox8->Enabled = true;
	checkBox9->Enabled = true;

	textBox20->Text = "";
	button3->Enabled = false;
	button2->Enabled = true;
	button20->Enabled = false;
	record = false;

	fileEMGRecord.close();
	fileIMURecord.close();
	textBox20->ReadOnly = false;
	textBox18->Text = "Stopped Recording!";
	RecordTimer->Stop();
}

		 //main loop
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	//timer loop

	timer1->Stop();

	int ex(0);

	try {

		// enter if playing back from FILE
		if (myoStreaming == false && fileOpened == true) {
			
			if (playbackLoop){
				playbackEMG(openEMGFile);

				playbackIMU(openIMUFile);

			}
		
			if ((!(checkBox6->Checked) && currentNumberLinesEmgPlayback >= maxNumberLinesEmgPlayback)) // || (!(checkBox6->Checked) && currentNumberLinesImuPlayback >= maxNumberLinesImuPlayback))
			{
				playbackLoop = false;
			}
			else {
				playbackLoop = true;
			}
			if (playbackLoop){
				if (currentNumberLinesEmgPlayback >= maxNumberLinesEmgPlayback) {
					currentNumberLinesEmgPlayback = 0;
				}
				if (currentNumberLinesImuPlayback >= maxNumberLinesImuPlayback) {
					currentNumberLinesImuPlayback = 0;
				}

			}

			progressBar1->Maximum = maxNumberLinesEmgPlayback;

			if (currentNumberLinesEmgPlayback <= maxNumberLinesEmgPlayback){
				progressBar1->Value = currentNumberLinesEmgPlayback;
				label39->Text = "" + (currentNumberLinesEmgPlayback)* 100 / (maxNumberLinesEmgPlayback)+"%";
			}

		}
		else {
			deviceMyo.hub.run(1000 / rrate);
		}

		int p = deviceMyo.collector.iteration_emg - deviceMyo.collector.lastCall;
		int o = p & 127;
		int q = deviceMyo.collector.sampling;

		while (o >= q)
		{
			
			//calculate features after minimum samples taken
			deviceMyo.collector.featCalc();

			if (deviceMyo.collector.armed) {
				classifier_training();
			}
			
			if (classify){
				run_classifier();
			}

			p = deviceMyo.collector.iteration_emg - deviceMyo.collector.lastCall;
			o = p & 127;
		}
		// IMU outside because iteration_emg is incremented inside of onEMG event, but IMU is not
		deviceMyo.collector.iteration_imu++;
		deviceMyo.collector.iteration_imu &= 127;

	
		// displays graph unviersally
		
		int it_emg_view = (deviceMyo.collector.iteration_emg - 1) & 127;
		int it_imu_view = (deviceMyo.collector.iteration_imu - 1) & 127;

		// should enter whenever data is being processed
		if (myoStreaming == true || playbackLoop == true){

			switch (tabSelected)
			{
			case input:
				
				updateStatus();

				break;

			case imu:

				Display_IMU_CB4(chart6); // displays chart6 based on comboBox4

				Display_IMU_chart_area(comboBox5, chart5);
				
				deviceMyo.collector.iteration_imu = 0; //Necessary

				printIMU(it_imu_view);
				
				break;

			case emg:
				deviceMyo.collector.sampling = (int)numericUpDown2->Value;

				deviceMyo.collector.window_length = (int)numericUpDown3->Value;

				Display_EMG(deviceMyo.collector);

				printEMG(deviceMyo.collector.iteration_emg&127); //RF used to be it_emg_view but i

				break;

			case feature:
				break;

			case classifier:
				//updates the # of gestures and # of sampmles textboxes
				textBox29->Text = "" + deviceMyo.collector.currentTotalClasses;
				textBox30->Text = "" + deviceMyo.collector.window_index;

				//updates "armed" status on classifier page
				if (deviceMyo.collector.armed == true) {
					textBox35->Text = "armed";
				}
				else { 
					textBox35->Text = "not armed"; 
				}


				if (accuracy_file_created == 5) {
					get_accuracy();
					accuracy_file_created = 0;
				}
				if (accuracy_file_created > 0) {
					accuracy_file_created++;
				}
				
				
				if (textBox36->Text != "" && comboBox10->Items->Count != 0) {
					button12->Enabled = true;
				}
				else {
					button12->Enabled = false;
				}

				if (!classify) { 
					textBox36->Enabled = true;
				}
				else{ 
					textBox36->Enabled = false;
				}

				//plots MMAV chart
				if (checkBox5->Checked == true) {
					mmav_display_line(deviceMyo.collector);
					display_IMU_CB11_CH7();
					label76->Text = "" + deviceMyo.collector.avg_mav;
				}
				
				deviceMyo.collector.iteration_imu = 0; //test later
								
				break;

			case output:
				break;

			}
		
		}


		if (record == true){
			recordData(it_emg_view, it_imu_view);
		}

		Application::DoEvents();

	}
	
	catch (int)
	{
		textBox1->Text = "Error!";
		return;
	}
	
	if (endtimer1 == false){
		timer1->Start();
	}
}

private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
	//"Add" in classifier
	
	if (comboBox10->Items->Contains(textBox14->Text)) {
		MessageBox::Show("Warning: Gesture name '"+textBox14->Text + "' already exists!",
			"Myo Gesture Classification Sheet", MessageBoxButtons::OK,
			MessageBoxIcon::Asterisk);
	}
	else {
		
		//String^ TempStr = gcnew String(textBox14->Text.c_str());
		std::string TempStr = msclr::interop::marshal_as<std::string>(textBox14->Text);
		gestureNames[deviceMyo.collector.currentTotalClasses] = TempStr;

		deviceMyo.collector.currentTotalClasses++;

		//gesture combobox 10
		comboBox10->Items->Add(textBox14->Text);

		comboBox10->SelectedItem = textBox14->Text;

		deviceMyo.collector.classifier_selected_class_index = comboBox10->SelectedIndex;

		button8->Enabled = true;
	}
}

private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
}

 /*
 Button 20 is place marker
 Button 2 is record
 Button 3 is stop record
 */
private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
	placeMarkerEMG = true;
	placeMarkerIMU = true;
}
		 
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {

	int openFileLineNumbers = 0;
	std::string line1;
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		System::IO::StreamReader ^ sr = gcnew
			System::IO::StreamReader(openFileDialog1->FileName);

		
		stdOpenEMGFile = context.marshal_as<std::string>(openFileDialog1->FileName);
		
		System::IO::FileStream^ fs = System::IO::File::OpenRead(openFileDialog1->FileName);
		
	}
		
	openEMGFile.open(stdOpenEMGFile);
		
		if (openEMGFile.is_open()){
			
			while (std::getline(openEMGFile, line1))
			{
				++maxNumberLinesEmgPlayback;
				textBox22->Text = "" + maxNumberLinesEmgPlayback; //db
			}
			fileOpened = true;
			textBox19->Text = System::IO::Path::GetFileName(openFileDialog1->FileName);

			button18->Enabled = true; //"Play file"
			openEMGFile.close();
			openEMGFile.open(stdOpenEMGFile);

		}

		else{
			textBox19->Text = ("File failed to load!");
		}
		/* db - this piece of code should be in Serie_radar_1
		for (int i(0); i < 3; i++)
		{
			chartEMG[i]->ChartAreas->Add("area");
		}

		for (int i(0); i < 2; i++)
		{
			chartEMG[i]->Legends->Clear();
			chartEMG[i]->Series->Clear();
		}

		
		*/
		
	

	}


private: System::Void button19_Click(System::Object^  sender, System::EventArgs^  e) {
	/*saveFileDialog1->ShowDialog();
	saveFileDialog1->CreatePrompt = true;
	saveFileDialog1->OverwritePrompt = true;

	// Set the file name to myText.txt, set the type filter 
	// to text files, and set the initial directory to the 
	// MyDocuments folder.
	saveFileDialog1->FileName = "myText";
	// DefaultExt is only used when "All files" is selected from 
	// the filter box and no extension is specified by the user.
	saveFileDialog1->DefaultExt = "txt";
	saveFileDialog1->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";
	saveFileDialog1->InitialDirectory = ""; //add directory
		//Environment->GetFolderPath(Environment::SpecialFolder::MyDocuments); example

	// Call ShowDialog and check for a return value of DialogResult.OK, 
	// which indicates that the file was saved. 
	/*DialogResult result = saveFileDialog1->ShowDialog();
	System::IO::Stream^ fileStream;
	if (System::IO::result == DialogResult::OK)
	{
		fileStream = saveFileDialog1->OpenFile();
		userInput->Position = 0;
		userInput->WriteTo(fileStream);
		fileStream->Close();
	}
	*/
}

		 //playback button
private: System::Void button18_Click(System::Object^  sender, System::EventArgs^  e) {

	timer1->Stop();

	myoStreaming = false;

	playbackLoop = true;
	
	currentNumberLinesImuPlayback = 0;

	currentNumberLinesEmgPlayback = 0;

	
	timer1->Start();

}



private: System::Void folderBrowserDialog1_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Forms::DialogResult result = folderBrowserDialog1->ShowDialog();
	if (result == System::Windows::Forms::DialogResult::OK)
		
	{
		userRecordDirectory = folderBrowserDialog1->SelectedPath;
		
	}
	//folder browser for choosing where to save recordings
}
private: System::Void button23_Click(System::Object^  sender, System::EventArgs^  e) {
	
	std::string line1;
	if (openFileDialog2->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{

		System::IO::StreamReader ^ sr = gcnew
			System::IO::StreamReader(openFileDialog2->FileName);

		stdOpenIMUFile = context.marshal_as<std::string>(openFileDialog2->FileName);

		System::IO::FileStream^ fs = System::IO::File::OpenRead(openFileDialog2->FileName);

	}

	openIMUFile.open(stdOpenIMUFile);

	if (openIMUFile.is_open()){

		while (std::getline(openIMUFile, line1))
		{
			++maxNumberLinesImuPlayback;
		}
		fileOpened = true;
		textBox16->Text = System::IO::Path::GetFileName(openFileDialog2->FileName);

		button18->Enabled = true; //"Play file"
		openIMUFile.close();
		openIMUFile.open(stdOpenIMUFile);
	}

	else{
		textBox16->Text = ("File failed to load!");
	}

}

private: System::Void RecordTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
	recordSeconds++;
	if (recordSeconds == 60){
		recordSeconds = 0;
		recordMinutes++;
		if (recordMinutes == 60){
			recordHours++;
			recordMinutes = 0;
		}

	}
	if (recordHours != 0){
		textBox18->Text = "" + recordHours + ":" + recordMinutes + ":" + recordSeconds;
	}
	else{
		if (recordSeconds < 10){
			textBox18->Text = "" + recordMinutes + ":0" + recordSeconds;
		}
		else{

			textBox18->Text = "" + recordMinutes + ":" + recordSeconds;
		}
	}
}


/////////

// myo vibration
private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) {
	if (deviceMyo.myo){
		deviceMyo.myo->vibrate(myo::Myo::vibrationShort);
	}
}
private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
	if(deviceMyo.myo2)
		deviceMyo.myo2->vibrate(myo::Myo::vibrationShort);
}

// next 4 button events for Play/Pause on IMU, EMG Tab
private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) {

	myoStreaming = true;
	endtimer1 = false;

	timer1->Start();
}
private: System::Void button29_Click(System::Object^  sender, System::EventArgs^  e) {

	textBox34->Text = "Paused";

	myoStreaming = false;

	endtimer1 = true;

}
private: System::Void button31_Click(System::Object^  sender, System::EventArgs^  e) {

	myoStreaming = true;
	endtimer1 = false;

	timer1->Start();
}
private: System::Void button30_Click(System::Object^  sender, System::EventArgs^  e) {

	textBox34->Text = "Paused";

	myoStreaming = false;

	endtimer1 = true;
}
//

private: System::Void button32_Click(System::Object^  sender, System::EventArgs^  e) {
	textBox34->Text = "Paused";

	myoStreaming = false;

	endtimer1 = true;

	
}

private: System::Void comboBox3_SelectedIndexChanged_1(System::Object^  sender, System::EventArgs^  e) {
	if (comboBox3->SelectedIndex == 1){
		groupBox10->Visible = false;	//Hide myo 1
		groupBox12->Visible = true;		//Show myo 2
	}
	else{
		groupBox10->Visible = true;		//Hide myo 1
		groupBox12->Visible = false;	//Show myo 2

	}
	
}
private: System::Void tabPage2_Enter(System::Object^  sender, System::EventArgs^  e) {

	tabSelected = imu;

	comboBox3->SelectedIndex = 0;
	comboBox4->SelectedIndex = 0;
	comboBox5->SelectedIndex = 3;

}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	// EMG tab
	init_EMG_charts();

	// classifier tab
	init_mmav_chart();

	// IMU tab
	init_IMU_charts();

	deviceMyo.collector.load_trainer_array();

	comboBox12->SelectedIndex = 1;

	svm_kernel_type = 1;

}

private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	timer1->Stop();
	
	deviceMyo.collector.activate_feature = false;
	deviceMyo.collector.activate_emg = false;
	deviceMyo.collector.activate_gyro = false;
	deviceMyo.collector.activate_accel = false;
	deviceMyo.collector.activate_ori = false;
	deviceMyo.stop_emg();
	deviceMyo.stop_listener();
	//Application::DoEvents();
	this->~MyForm();
}
		 /*
		 
		 private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	myoStreaming = false;
	playbackLoop = true;

	currentNumberLinesImuPlayback = 0;

	currentNumberLinesEmgPlayback = 0;

	timer1->Start();
}
		 
		 */

private: System::Void comboBox4_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	selectedChart_Cbox4 = comboBox4->SelectedIndex;
	Relabel_IMU_chart_area(comboBox4,chart6);
}
private: System::Void comboBox5_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	selectedChart_Cbox5 = comboBox5->SelectedIndex;
	Relabel_IMU_chart_area(comboBox5, chart5);
}
private: System::Void comboBox11_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	selectedChart_Cbox11 = comboBox11->SelectedIndex;
	Relabel_IMU_chart_area(comboBox11, chart7);
} 

		 // classifier enter
private: System::Void tabPage6_Enter(System::Object^  sender, System::EventArgs^  e) {
	tabSelected = classifier;
	comboBox11->SelectedIndex = 0;
	ite = 100;
	xmin = 0;
	xmax = 100;
	deviceMyo.collector.iteration_emg = 0;
}
private: System::Void tabPage3_Enter(System::Object^  sender, System::EventArgs^  e) {
	tabSelected = emg;
	comboBox6->SelectedIndex = 0;
	comboBox8->SelectedIndex = 1;
	comboBox7->SelectedIndex = 2;
	comboBox9->SelectedIndex = 3;

}
private: System::Void comboBox6_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	Relabel_EMG_chart_area(chart1);
}
private: System::Void comboBox7_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	//Relabel_EMG_chart_area(chart2);
}
private: System::Void comboBox8_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
	Relabel_EMG_chart_area(chart1);
}
private: System::Void comboBox9_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	//Relabel_EMG_chart_area(chart2);
}
private: System::Void checkBox7_CheckStateChanged(System::Object^  sender, System::EventArgs^  e) {
	Relabel_EMG_chart_area(chart1);
	//Relabel_EMG_chart_area(chart2);

}
private: System::Void numericUpDown5_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

	deviceMyo.collector.threshold = (int)numericUpDown5->Value;

}
private: System::Void tabPage6_Leave(System::Object^  sender, System::EventArgs^  e) {

	chart4->Series["mmav"]->Points->Clear();
	chart4->Series["threshold"]->Points->Clear();

}

// load charts button


private: System::Void tabPage5_Enter(System::Object^  sender, System::EventArgs^  e) {
	tabSelected = output;
}

private: System::Void tabPage4_Enter(System::Object^  sender, System::EventArgs^  e) {
	tabSelected = feature;
}


private: System::Void tabPage1_Enter(System::Object^  sender, System::EventArgs^  e) {
	tabSelected = input;
}






private: System::Void button8_Click_1(System::Object^  sender, System::EventArgs^  e) {
	//train/stop button
	if (deviceMyo.collector.armed) {

		disarm_trainer();

	}
	else if (!deviceMyo.collector.armed) {
		deviceMyo.collector.window_index = 0;
		deviceMyo.collector.armed = true;
		// retrieve old window_index from radio button ... option
		
		button8->Text = "Stop";
	}

	

}
private: System::Void comboBox10_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {

	deviceMyo.collector.classifier_selected_class_index = comboBox10->SelectedIndex;
	deviceMyo.collector.armed = false;

}

private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
	//"remove / delete all " button in classifier
	comboBox10->Items->Clear();
	deviceMyo.collector.currentTotalClasses = 0;
	textBox14->Text = "";
	comboBox10->Text = "";
	for (int i(0); i < maxClasses; i++)
	{
		gestureNames[i] = "";
	}

	for (int i(0); i < maxClasses; i++) {
		deviceMyo.collector.numWC[i] = 0;
		for (int j(0); j < maxWindowNumber; j++) {
			for (int k(0); k < (maxFeatures);k++) {
				deviceMyo.collector.classifierTrainer[i][j][k]=0;
			}
		}
	}

}

private: System::Void button12_Click_1(System::Object^  sender, System::EventArgs^  e) {
	// create model button

	if (comboBox12->SelectedIndex < 10) {
		svm_create_model();
	}
	else if (comboBox12->SelectedIndex == 10) {

		

		lda_driver();


	}
	
	

}

private: System::Void button19_Click_1(System::Object^  sender, System::EventArgs^  e) {

	System::Windows::Forms::DialogResult result = folderBrowserDialog2->ShowDialog();
	if (result == System::Windows::Forms::DialogResult::OK)

	{
		LDARecordDirectory = folderBrowserDialog2->SelectedPath;

	}
}

private: System::Void button33_Click(System::Object^  sender, System::EventArgs^  e) {
	if (classify) {
		classify = false;
		button33->Text = "Start Classifier";
	}
	else {
		classify = true;
		button33->Text = "Stop Classifier";

		LDAPredictInputFileName = LDARecordDirectory + "\\" + textBox36->Text + ".labels.txt";
		stdLDAPredictInputFileName = context.marshal_as<std::string>(LDAPredictInputFileName);
		openLDAPredictionOutput.open(stdLDAPredictInputFileName);
		
		int i = 0;

		while (openLDAPredictionOutput.good()) {
			openLDAPredictionOutput >> gestureNames[i];
			openLDAPredictionOutput >> pictures[i];
			i++;
		}

		deviceMyo.collector.currentTotalClasses = i;

		openLDAPredictionOutput.close();


	}
	//start/stop classifier button
	
	// flag to start classifying continuously
	
	
	
}
private: System::Void button34_Click(System::Object^  sender, System::EventArgs^  e) {
	
	
} 
private: System::Void button35_Click(System::Object^  sender, System::EventArgs^  e) {

	// predict button


}
private: System::Void button35_Click_1(System::Object^  sender, System::EventArgs^  e) {

	

}
private: System::Void comboBox12_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {

	svm_kernel_type = comboBox12->SelectedIndex;

	if (svm_kernel_type > 4) {
		svm_kernel_type -= 5;
	}
}

private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {

	if (comboBox12->SelectedIndex < 10) 
	{
		svm_create_training_percentage();
	}
	else if (comboBox12->SelectedIndex == 10) {

	}

}




private: System::Void button34_Click_1(System::Object^  sender, System::EventArgs^  e) {

	System::Windows::Forms::DialogResult result2 = openFileDialog3->ShowDialog();
	if (result2 == System::Windows::Forms::DialogResult::OK) {
	
		PictureDirectory = openFileDialog3->FileName ;

		msclr::interop::marshal_context context;
		std::string PictureDirectory_std = context.marshal_as<std::string>(PictureDirectory);

		pictures[deviceMyo.collector.classifier_selected_class_index] = PictureDirectory_std;

	}

}

private: System::Void button35_Click_2(System::Object^  sender, System::EventArgs^  e) {
	try {
		String^ PictureDirectory_system = gcnew String(pictures[deviceMyo.collector.classifier_selected_class_index].c_str());

		pictureBox1->Load(PictureDirectory_system);

	}
	catch (...) {
		MessageBox::Show("NOT A PICTURE!");
	}
	

}


private: System::Void button36_Click(System::Object^  sender, System::EventArgs^  e) {
	// save training data button

	training_data_name = folderBrowserDialog2->SelectedPath + "/" + textBox36->Text + "_training_data.txt";
	stdRecordLDAFileName = context.marshal_as<std::string>(training_data_name);
	ofile3.open(stdRecordLDAFileName);

	for (int i = 0; i < deviceMyo.collector.currentTotalClasses; i++)
	{
		ofile3 << i << "\n";
	
		for (int k = 0; k < (deviceMyo.collector.numWC[i]); k++) {

			for (int j = 0; j < (maxFeatures); j++) {

				ofile3 << deviceMyo.collector.classifierTrainer[i][k][j] << " ";
			}

		}
	}
	ofile3.close();

}


};

} 
