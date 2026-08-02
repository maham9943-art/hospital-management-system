#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class Patient;
vector<Patient>allPatients;
int nextPatientId=1;

class Patient
{
	private:
		int patientId;
		string patientName;
		int age;
		string gender;
		string diagnosis;
		string contactNo;
	public:
		void display()
		{
			cout<<"ID: "<<patientId<<endl;
			cout<<"Name: "<<patientName<<endl;
			cout<<"Age: "<<age<<endl;
			cout<<"Gender: "<<gender<<endl;
			cout<<"Diagnosis: "<<diagnosis<<endl;
			cout<<"Contact Number: "<<contactNo<<endl;
			cout<<"------------------------------------------\n"<<endl;
		}
		void displaySummary()
		{
			cout<<"ID: "<<patientId<<endl;
			cout<<"Name: "<<patientName<<endl;
			cout<<"Age: "<<age<<endl;
			cout<<"Gender: "<<gender<<endl;
			cout<<"Contact Number: "<<contactNo<<endl;
			cout<<endl;
		}
		string getPatientName()
		{
			return patientName;
		}
		int getPatientId()
		{
			return patientId;
		}
		void addPatient()
		{
			cout<<"Enter Name: ";
			getline(cin,patientName);
			cout<<"\n Enter Age: ";
			cin>>age;
			cin.ignore();
			cout<<"\n Enter Gender: ";
			getline(cin,gender);
			cout<<"\n Enter Diagnosis: ";
			getline(cin,diagnosis);
			cout<<"\n Enter Contact Number: ";
			getline(cin,contactNo);
			
			
			patientId=nextPatientId++;//nextpatientid will hold the count of ids and give the current no to patientId then increment will happen
			allPatients.push_back(*this);//*this here is actually (this is pointing to the current object whose details are filled in. and * is saying we don't want address but the actual material.)
			saveAllPatients(allPatients);
			cout<<"\nPatient added successfully. ID: "<<patientId<<endl;
		}
		static void updatePatient()
		{
			vector<int>matchingIdx;
			bool found=false;
			while(!found)
			{
			string name;
			cout<<"\nEnter Patient Name: ";
			getline(cin,name);
			
			for(int i=0;i<allPatients.size();i++)
			{
				if(allPatients[i].patientName==name)
				{
					matchingIdx.push_back(i);
				}
			}
			if(matchingIdx.empty())
			{
				cout<<"\nNo patient found!"<<endl;
				cout<<"1. Try again\n2. Exit\n";
				int choice;
				cin>>choice;
				cin.ignore();
				if(choice==1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
			else{
				found=true;
			}
			}
			cout<<"\nFound "<<matchingIdx.size()<<" patient(s):\n"<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ";
				allPatients[idx].display();
			}
			int pChoice;
			while(true)
			{
				cout<<"\nSelect which patient to update (1 to "<<matchingIdx.size()<<") or select 0 to go back to Main Menu: ";
				cin>>pChoice;
				if(pChoice==0)
				{
					cout<<"\nReturning to Main Menu...";
					return;
				}
				if(pChoice<1||pChoice>matchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					break;
				}
			}
			
			int selectedIdx=matchingIdx[pChoice-1];
			cout<<"\nWhat do you want to update?"<<endl;
			cout<<"1.Name"<<endl;
			cout<<"2.Age"<<endl;
			cout<<"3.Gender"<<endl;
			cout<<"4.Diagnosis"<<endl;
			cout<<"5.Contact Number"<<endl;
			cout<<"\nEnter Choice: ";
			int choice;
			cin>>choice;
			cin.ignore();
			switch(choice)
			{
				case 1:
					cout<<"\nEnter new Name: ";
					getline(cin,allPatients[selectedIdx].patientName);
					break;
				case 2:
					cout<<"\nEnter new Age: ";
					cin>>allPatients[selectedIdx].age;
					cin.ignore();
					break;
				case 3:
					cout<<"\nEnter new Gender: ";
					getline(cin,allPatients[selectedIdx].gender);
					break;
				case 4:
					cout<<"\nEnter new Diagnosis: ";
					getline(cin,allPatients[selectedIdx].diagnosis);
					break;
				case 5:
					cout<<"Enter new Contact Number: ";
					getline(cin,allPatients[selectedIdx].contactNo);
					break;
				default:
					cout<<"\nInvalid option!"<<endl;
			}
			saveAllPatients(allPatients);
			cout<<"\nUpdated successfully!"<<endl;			
		}
		static void viewPatients()
		{
			if(allPatients.empty())
			{
				cout<<"\nNo patient found in the system.\n";
				return;
			}
			cout<<"\n==== All Patients ===="<<endl;
			for(auto& p: allPatients)
			{
				p.display();
			}
			cout<<"\nTotal patients: "<<allPatients.size()<<endl;
		}
		static void searchPatient()
		{
			vector<int>matchingIdx;
			bool found=false;
			while(!found)
			{
			string name;
			cout<<"\nEnter Patient Name to search: ";
			getline(cin,name);
			
			for(int i=0;i<allPatients.size();i++)
			{
				if(allPatients[i].patientName==name)
				{
					matchingIdx.push_back(i);
				}
			}
			if(matchingIdx.empty())
			{
				cout<<"\nNo patient found with name: "<<name<<endl;
				cout<<"1. Try again\n2. Exit\n";
				int choice;
				cin>>choice;
				cin.ignore();
				if(choice==1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
			else{
				found=true;
			}
			}
			//show id+name only
			cout<<"\nFound "<<matchingIdx.size()<<" patient(s):\n"<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ID: "<<	allPatients[idx].patientId<<endl;
				cout<<"Name: "<<allPatients[idx].patientName<<endl;
			}
			
			int choice;
			while(true)
			{
				cout<<"\nSelect patient to view full details (1-"<<matchingIdx.size()<<") or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					return;
				}
				if(choice<1||choice>matchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					break;
				}
			}
			int selected=matchingIdx[choice-1];
			cout<<"\n--- Full Details ---\n";
			allPatients[selected].display();
		}
		
		friend vector<Patient>loadAllPatients();
		friend void saveAllPatients(vector<Patient>&patients);
};

//Doctor class declaration
class Doctor;
vector<Doctor>allDoctors;
int nextDoctorId=1;
class Doctor
{
	private:
		int doctorId;
		string doctorName;
		string specialization;
		string status;
		string contactNo;
	public:
		void display()
		{
			cout<<"ID: "<<doctorId<<endl;
			cout<<"Name: "<<doctorName<<endl;
			cout<<"Specialization: "<<specialization<<endl;
			cout<<"Status: "<<status<<endl;
			cout<<"Contact Number: "<<contactNo<<endl;
			cout<<"------------------------------------------\n";
			cout<<endl;
		}
		void displaySummary()
		{
			cout<<"\nID: "<<doctorId<<endl;
			cout<<"Name: "<<doctorName<<endl;
			cout<<"Specialization: "<<specialization<<endl;
			cout<<"Status: "<<status<<endl;
		}
		string getDoctorName()
		{
			return doctorName;
		}
		int getDoctorId()
		{
			return doctorId;
		}
		string getStatus()
		{
			return status;
		}
		void addDoctor()
		{
			cout<<"\nEnter Name: ";
			getline(cin,doctorName);
			cout<<"\nEnter Specialization: ";
			getline(cin,specialization);
			cout<<"\nEnter Status(Available, On Leave, Busy): ";
			getline(cin,status);
			cout<<"\nEnter Contact Number: ";
			getline(cin,contactNo);
			
			doctorId=nextDoctorId++;
			allDoctors.push_back(*this);
			saveAllDoctors(allDoctors);
			cout<<"\nDoctor added successfully. ID: "<<doctorId<<endl;
		}
		static void updateDoctor()
		{
			vector<int>matchingIdx;
			bool found=false;
			while(!found)
			{
			string name;
			cout<<"\nEnter Doctor Name: ";
			getline(cin,name);
			
			
			for(int i=0;i<allDoctors.size();i++)
			{
				if(allDoctors[i].doctorName==name)
				{
					matchingIdx.push_back(i);
				}
			}
			if(matchingIdx.empty())
			{
				cout<<"\nNo doctor found!"<<endl;
				cout<<"1. Try again\n2. Exit\n";
				int choice;
				cin>>choice;
				cin.ignore();
				if(choice==1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
			else{
				found=true;
			}
			}
			cout<<"\nFound "<<matchingIdx.size()<<" doctor(s):\n"<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ";
				allDoctors[idx].display();
			}
			int pChoice;
			while(true)
			{
				cout<<"\nSelect which doctor to update (1 to "<<matchingIdx.size()<<") or select 0 to go back to Main Menu: ";
				cin>>pChoice;
				if(pChoice==0)
				{
					cout<<"\nReturning to Main Menu...";
					return;
				}
				if(pChoice<1||pChoice>matchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					break;
				}
			}
			
			int selectedIdx=matchingIdx[pChoice-1];
			cout<<"\nWhat do you want to update?"<<endl;
			cout<<"1.Name"<<endl;
			cout<<"2.specialization"<<endl;
			cout<<"3.Contact Number"<<endl;
			cout<<"\nEnter Choice: ";
			int choice;
			cin>>choice;
			cin.ignore();
			switch(choice)
			{
				case 1:
					cout<<"\nEnter Name: ";
					getline(cin,allDoctors[selectedIdx].doctorName);
					break;
				case 2:
					cout<<"\nEnter specializaion: ";
					getline(cin,allDoctors[selectedIdx].specialization);
					break;
				case 3:
					cout<<"\nEnter new Contact Number: ";
					getline(cin,allDoctors[selectedIdx].contactNo);
					break;
				default:
					cout<<"\nInvalid option!"<<endl;
			}
			saveAllDoctors(allDoctors);
			cout<<"\nUpdated successfully!"<<endl;
		}
		static void viewDoctors()
		{
			if(allDoctors.empty())
			{
				cout<<"\nNo doctor found in the system.";
				return;
			}
			cout<<"\n==== All Doctors ===="<<endl;
			for(auto& d: allDoctors)
			{
				d.display();
			}
			cout<<"\nTotal doctors: "<<allDoctors.size()<<endl;
		}
		static void searchDoctor()
		{
			vector<int>matchingIdx;
			bool found=false;
			while(!found)
			{
			string name;
			cout<<"\nEnter Doctor Name to search: ";
			getline(cin,name);
			
			for(int i=0;i<allDoctors.size();i++)
			{
				if(allDoctors[i].doctorName==name)
				{
					matchingIdx.push_back(i);
				}
			}
			if(matchingIdx.empty())
			{
				cout<<"\nNo doctor found with name: "<<name<<endl;
				cout<<"1. Try again\n2. Exit\n";
				int choice;
				cin>>choice;
				cin.ignore();
				if(choice==1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
			else{
				found=true;
			}
			}
			//show id+name only
			cout<<"\nFound "<<matchingIdx.size()<<" doctor(s):\n"<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ID: "<<	allDoctors[idx].doctorId<<endl;
				cout<<"Name: "<<allDoctors[idx].doctorName<<endl;
			}
			
			int choice;
			while(true)
			{
				cout<<"\nSelect doctor to view full details (1-"<<matchingIdx.size()<<") or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					return;
				}
				if(choice<1||choice>matchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					break;
				}
			}
			int selected=matchingIdx[choice-1];
			cout<<"\n--- Full Details ---\n";
			allDoctors[selected].display();
		}
		static void updateDoctorStatus()
		{
			vector<int>matchingIdx;
			bool found=false;
			while(!found)
			{
			string name;
			cout<<"\nEnter Doctor Name to search: ";
			getline(cin,name);
			
			for(int i=0;i<allDoctors.size();i++)
			{
				if(allDoctors[i].doctorName==name)
				{
					matchingIdx.push_back(i);
				}
			}
			if(matchingIdx.empty())
			{
				cout<<"\nNo doctor found with name: "<<name<<endl;
				cout<<"1. Try again\n2. Exit\n";
				int choice;
				cin>>choice;
				cin.ignore();
				if(choice==1)
				{
					continue;
				}
				else
				{
					return;
				}
			}
			else{
				found=true;
			}
			}
			//show id+name+status only
			cout<<"\nFound "<<matchingIdx.size()<<" doctor(s):\n"<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ID: "<<	allDoctors[idx].doctorId<<endl;
				cout<<"Name: "<<allDoctors[idx].doctorName<<endl;
				cout<<"Status: "<<allDoctors[idx].status<<endl;
			}
			
			int choice;
			while(true)
			{
				cout<<"\nSelect doctor to change status (1-"<<matchingIdx.size()<<") or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					return;
				}
				if(choice<1||choice>matchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					break;
				}
			}
			int selectedIdx=matchingIdx[choice-1];
			cout<<"\nEnter status: ";
			getline(cin,allDoctors[selectedIdx].status);
			cin.ignore();
			
			saveAllDoctors(allDoctors);
			cout<<"\nUpdated successfully!"<<endl;
			
			cout<<"Updated status: "<<allDoctors[selectedIdx].status<<endl;
		}
		
		friend vector<Doctor>loadAllDoctors();
		friend void saveAllDoctors(vector<Doctor>&Doctors);
};

//class appoinments
class Appointment;
vector<Appointment>allAppointments;
int nextAppointmentId=1;
class Appointment
{
	private:
		int appointmentId;
		int patientId;
		int doctorId;
		string appointmentDate;
		string appointmentTime;
	public:
		void display()
		{
			cout<<"\nAppointment Id: "<<appointmentId<<endl;
			cout<<"PatientId: "<<patientId<<endl;
			cout<<"DoctorId: "<<doctorId<<endl;
			cout<<"Date: "<<appointmentDate<<endl;
			cout<<"Time: "<<appointmentTime<<endl;
			cout<<"------------------------------------------\n";
			cout<<endl;
		}
		void bookAppointment()
		{
			int selectedPatientId;
			int selectedDoctorId;
			bool pfound=false;
			vector<int>MatchingIdx;
			while(!pfound)
			{
				string pname;
				cout<<"\nEnter Patient Name: ";
				getline(cin,pname);
				for(int i=0;i<allPatients.size();i++)
				{
					if(allPatients[i].getPatientName()==pname)
					{
						MatchingIdx.push_back(i);
					}
				}
	
				if(MatchingIdx.empty())
				{
					cout<<"\nNo patient found with name: "<<pname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						cout<<"Booking cancelled."<<endl;
						return;
					}
				}
				else
				{
					pfound=true;
				}
			}
			cout<<"\nFound "<<MatchingIdx.size()<<" patients(s):\n"<<endl;
			for(int j=0;j<MatchingIdx.size();j++)
			{
				int idx= MatchingIdx[j];
				cout<<(j+1)<<". ";
				allPatients[idx].displaySummary();
			}
			int choice;
			bool found=false;
			while(!found)
			{
				cout<<"\nSelect patient to book appointment or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					cout<<"\nReturning..."<<endl;
					return;
				}
				if(choice<1||choice>MatchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					found=true;
				}
			}
			selectedPatientId=allPatients[MatchingIdx[choice-1]].getPatientId();
			cout<<"\nSelect patient to book appointment or 0 to go back: ";
			cin>>choice;
			cin.ignore();
			if(choice==0)
			{
				cout<<"\nReturning..."<<endl;
				return;
			}
			if(choice<1||choice>MatchingIdx.size())
			{
				cout<<"\nInvalid choice!"<<endl;
			}
			else
			{
				selectedPatientId=allPatients[MatchingIdx[choice-1]].getPatientId();
			}
			
			bool Found=false;
			while(!Found)
			{
				vector<int>matchingIdx;
				string dname;
				cout<<"\nEnter Doctor Name: ";
				getline(cin,dname);
				
				for(int i=0;i<allDoctors.size();i++)
				{
					if(allDoctors[i].getDoctorName()==dname)
					{
						matchingIdx.push_back(i);
					}
				}
	
				if(matchingIdx.empty())
				{
					cout<<"\nNo doctor found with name: "<<dname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						cout<<"Booking cancelled."<<endl;
						return;
					}
				}
				else
				{
					cout<<"\nMathcing Doctors:\n";
					for(int j=0;j<matchingIdx.size();j++)
					{
						int idx=matchingIdx[j];
						cout<<(j+1)<<". ";
						allDoctors[idx].displaySummary();
					}
			
					int choice;
					cout<<"\nSelect Doctor: ";
					cin>>choice;
					cin.ignore();
					if(choice<1||choice>matchingIdx.size())
					{
						cout<<"\nInvalid choice!"<<endl;
						continue;
					}
					else
					{			
						int idx=matchingIdx[choice-1];
						if(allDoctors[idx].getStatus()!="Available"&&allDoctors[idx].getStatus()!="available")
						{
							cout<<"\nDoctor is not available.\nChoose 1 to book another doctor or 0 to go back.\n";
							int Choice;
							cin>>Choice;
							cin.ignore();
							if(Choice==1)
							{
								continue;
							}
							else if(Choice==0)
							{
								cout<<"\nReturning..."<<endl;
								return;
							}
						}
						else
						{
							selectedDoctorId=allDoctors[matchingIdx[choice-1]].getDoctorId();
							break;
						}
					}
				}
			}
			cout<<"\nEnter Date (YYYY-MM-DD): ";
			getline(cin,appointmentDate);
			cout<<"\nEnter Time (HH:MM): ";
			getline(cin,appointmentTime);
			
			appointmentId=nextAppointmentId++;
			patientId=selectedPatientId;
			doctorId=selectedDoctorId;
			allAppointments.push_back(*this);
			saveAllAppointments(allAppointments);
			
			cout<<"\nAppointment booked successfully! ID: "<<appointmentId<<endl;
		}
		
		static void rescheduleAppointment()
		{
			//search patient and choose
			bool found=false;
			vector<int>matchingIdx;
			while(!found)
			{
				string pname;
				cout<<"\nEnter Patient Name: ";
				getline(cin,pname);
				for(int i=0;i<allPatients.size();i++)
				{
					if(allPatients[i].getPatientName()==pname)
					{
						matchingIdx.push_back(i);
					}
				}
	
				if(matchingIdx.empty())
				{
					cout<<"\nNo patient found with name: "<<pname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						cout<<"Reschedule cancelled."<<endl;
						return;
					}
				}
				else
				{
					found=true;
				}
			}
			int selectedIdx;
			if(matchingIdx.size()==1)
			{
				selectedIdx=allPatients[matchingIdx[0]].getPatientId();
			}
			else
			{
				cout<<"\nFound "<<matchingIdx.size()<<" patient(s): "<<endl;
				for(int j=0;j<matchingIdx.size();j++)
				{
					int idx= matchingIdx[j];
					cout<<(j+1)<<". ";
					allPatients[idx].displaySummary();
				}
				int choice;
				cout<<"\nSelect Patient or select 0 to go back: ";
				cin>>choice;
				if(choice==0)
				{
					cout<<"\nReturning..."<<endl;
					return;
				}
				else
				{
					selectedIdx=allPatients[matchingIdx[choice-1]].getPatientId();
				}
			}
			//search patients appoinments and choose 
			vector<int>patientAppts;
			for(int i=0;i<allAppointments.size();i++)
			{
				if(allAppointments[i].patientId==selectedIdx)
				{
					patientAppts.push_back(i);
				}
			}
			if(patientAppts.empty())
			{
				cout<<"\nNo appointment found for this patient."<<endl;
				return;
			}
			int chosenIdx;
			if(patientAppts.size()==1)
			{
				chosenIdx=patientAppts[0];
			}
			else
			{
				cout<<"This patients has "<<patientAppts.size()<<" appointments:"<<endl;
				for(int j=0;j<patientAppts.size();j++)
				{
					int idx=patientAppts[j];
					cout<<(j+1)<<". Appointment ID: "<<allAppointments[idx].appointmentId<<endl;
					cout<<"Date: "<<allAppointments[idx].appointmentDate<<endl;
					cout<<"Time: "<<allAppointments[idx].appointmentTime<<endl;
					cout<<"Doctor ID: "<<allAppointments[idx].doctorId<<endl;
				}
				int choice;
				cout<<"\nSelect appointment to reschedule or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					cout<<"\nReturning..."<<endl;
					return;
				}
				else
				{
					chosenIdx=patientAppts[choice-1];
				}
			}
			while(true)
			{
				cout<<"\n1. Change Date\n2. Change Time\n3. Cancel(go back)"<<endl;
				int menuChoice;
				cout<<"Enter choice: ";
				cin>>menuChoice;
				cin.ignore();
				if(menuChoice==1)
				{
					//date edit
					cout<<"\nEnter new Date(YYYY-MM-DD): ";
					getline(cin,allAppointments[chosenIdx].appointmentDate);
					
				}
				else if(menuChoice==2)
				{
					//time edit
					cout<<"\nEnter new Time(HH-MM): ";
					getline(cin,allAppointments[chosenIdx].appointmentTime);
				}
				else if(menuChoice==3)
				{
					break;
				}
				else
				{
					cout<<"\nInvalid choice!"<<endl;
					continue;
				}
				cout<<"\nChange something else?\n1. Yes"<<endl;
				int again;
				cin>>again;
				cin.ignore();
				if(again==1)
				{
					continue;
				}
				else
				{
					break;
				}
			}
			saveAllAppointments(allAppointments);
			cout<<"\nAppointment rescheduled successfully!"<<endl;		
		}
		static void viewAppointments()
		{
			if(allAppointments.empty())
			{
				cout<<"No appointment found in the system.\n";
				return;
			}
			cout<<"\n==== All Appointments ===="<<endl;
			for(auto& a: allAppointments)
			{
				a.display();
			}
			cout<<"\nTotal appointments: "<<allAppointments.size()<<endl;	
		}
		
		static void searchAppointment()
		{
			bool found=false;
			vector<int>matchingIdx;
			while(!found)
			{
				string pname;
				cout<<"\nEnter Patient Name: ";
				getline(cin,pname);
				for(int i=0;i<allPatients.size();i++)
				{
					if(allPatients[i].getPatientName()==pname)
					{
						matchingIdx.push_back(i);
					}
				}
	
				if(matchingIdx.empty())
				{
					cout<<"\nNo patient found with name: "<<pname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						cout<<"\nReturning..."<<endl;
						return;
					}
				}
				else
				{
					found=true;
				}
			}
			int selectedIdx;
			cout<<"\nFound "<<matchingIdx.size()<<" patient(s): "<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ";
				allPatients[idx].displaySummary();
			}
			int choice;
			cout<<"\nSelect Patient or select 0 to go back: ";
			cin>>choice;
			if(choice==0)
			{
				cout<<"\nReturning..."<<endl;
				return;
				}
			else
			{
				selectedIdx=allPatients[matchingIdx[choice-1]].getPatientId();
			}
			//search patients appointments and choose appointment
			vector<int>patientAppts;
			for(int i=0;i<allAppointments.size();i++)
			{
				if(allAppointments[i].patientId==selectedIdx)
				{
					patientAppts.push_back(i);
				}
			}
			if(patientAppts.empty())
			{
				cout<<"\nNo appointment found for this patient."<<endl;
				return;
			}
			else
			{
				cout<<"\nThis patients has "<<patientAppts.size()<<" appointments:"<<endl;
				for(int j=0;j<patientAppts.size();j++)
				{
					int idx=patientAppts[j];
					allAppointments[idx].display();
				}
			}
		}
		
		friend vector<Appointment>loadAllAppointments();
		friend void saveAllAppointments(vector<Appointment>&Appointments);
};
class Bill;
vector<Bill>allBills;
int nextBillId=1;

class Bill
{
	private:
		int billId;
		int patientId;
		double billAmount;
	public:
		void generateBill()
		{
			bool pfound=false;
			vector<int>MatchingIdx;
			while(!pfound)
			{
				string pname;
				cout<<"\nEnter Patient Name: ";
				getline(cin,pname);
				for(int i=0;i<allPatients.size();i++)
				{
					if(allPatients[i].getPatientName()==pname)
					{
						MatchingIdx.push_back(i);
					}
				}
	
				if(MatchingIdx.empty())
				{
					cout<<"\nNo patient found with name: "<<pname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						return;
					}
				}
				else
				{
					pfound=true;
				}
			}
			int selectedPatientId;
			cout<<"\nFound "<<MatchingIdx.size()<<" patients(s):\n"<<endl;
			for(int j=0;j<MatchingIdx.size();j++)
			{
				int idx= MatchingIdx[j];
				cout<<(j+1)<<". ";
				allPatients[idx].displaySummary();
			}
			int choice;
			bool found=false;
			while(!found)
			{
				cout<<"\nSelect patient to generate bill or 0 to go back: ";
				cin>>choice;
				cin.ignore();
				if(choice==0)
				{
					cout<<"\nReturning..."<<endl;
					return;
				}
				if(choice<1||choice>MatchingIdx.size())
				{
					cout<<"\nInvalid choice!"<<endl;
				}
				else
				{
					found=true;
				}
			}
			selectedPatientId=allPatients[MatchingIdx[choice-1]].getPatientId();
			cout<<"\nEnter amount: ";
			cin>>billAmount;
			cin.ignore();
			
			billId=nextBillId++;
			patientId=selectedPatientId;
			allBills.push_back(*this);
			saveAllBills(allBills);
			cout<<"Bill generated successfully! ID: "<<billId<<endl;
		}
		static void viewBills()
		{
			if(allBills.empty())
			{
				cout<<"No bills found."<<endl;
				return;
			}
			cout<<"\n==== All Bills ===="<<endl;
			for(auto& b:allBills)
			{
				cout<<"Bill ID: "<<b.billId<<endl;
				cout<<"Patient ID: "<<b.patientId<<endl;
				cout<<"Bill Amount: "<<b.billAmount<<endl;	
			}
		}
		static void searchBill()
		{
			bool found=false;
			vector<int>matchingIdx;
			while(!found)
			{
				string pname;
				cout<<"\nEnter Patient Name: ";
				getline(cin,pname);
				for(int i=0;i<allPatients.size();i++)
				{
					if(allPatients[i].getPatientName()==pname)
					{
						matchingIdx.push_back(i);
					}
				}
	
				if(matchingIdx.empty())
				{
					cout<<"\nNo patient found with name: "<<pname<<endl;
					int choice;
					cout<<"1. Try again\n2. Exit\n";
					cin>>choice;
					cin.ignore();
					if(choice==1)
					{
						continue;
					}
					else
					{
						cout<<"\nReturning..."<<endl;
						return;
					}
				}
				else
				{
					found=true;
				}
			}
			int selectedIdx;
			cout<<"\nFound "<<matchingIdx.size()<<" patient(s): "<<endl;
			for(int j=0;j<matchingIdx.size();j++)
			{
				int idx= matchingIdx[j];
				cout<<(j+1)<<". ";
				allPatients[idx].displaySummary();
			}
			int choice;
			cout<<"\nSelect Patient or select 0 to go back: ";
			cin>>choice;
			if(choice==0)
			{
				cout<<"\nReturning..."<<endl;
				return;
				}
			else
			{
				selectedIdx=allPatients[matchingIdx[choice-1]].getPatientId();
			}
			//search patients bills 
			vector<int>patientBills;
			for(int i=0;i<allBills.size();i++)
			{
				if(allBills[i].patientId==selectedIdx)
				{
					patientBills.push_back(i);
				}
			}
			if(patientBills.empty())
			{
				cout<<"\nNo bill found for this patient."<<endl;
				return;
			}
			else
			{
				cout<<"\nThis patients has "<<patientBills.size()<<" bill(s):"<<endl;
				for(int j=0;j<patientBills.size();j++)
				{
					int idx=patientBills[j];
					cout<<"Bill ID: "<<allBills[idx].billId<<endl;
					cout<<"Bill Amount: "<<allBills[idx].billAmount<<endl;
				}
			}
		}
	
	
	friend vector<Bill>loadAllBills();
	friend void saveAllBills(vector<Bill>&Bills);
};

//loadallbills and saveallbills
void saveAllBills(vector<Bill>&bills)
{
	ofstream file("bills.txt");
	for(auto& b:bills)
	{
		file<<b.billId<<","<<b.patientId<<","<<b.billAmount<<endl;
	}
	file.close();
}
vector<Bill> loadAllBills()
{
	vector<Bill>bills;
	ifstream file("bills.txt");
	string line;
	while(getline(file,line))
	{
		if(line.empty())
		{
			continue;
		}
		Bill b;
		stringstream ss(line);
		string billIdStr,patientIdStr,billAmountStr;
		
		getline(ss,billIdStr,',');
		getline(ss,patientIdStr,',');
		getline(ss,billAmountStr,',');
		
		b.billId=stoi(billIdStr);
		b.patientId=stoi(patientIdStr);
		b.billAmount=stod(billAmountStr);
		bills.push_back(b);
		if(b.billId>=nextBillId)
		{
			nextBillId=b.billId+1;
		}
	}
	file.close();
	return bills;
}

//LOADALLAPPOINMENTS AND SAVEALLAPPOINMENTS
void saveAllAppointments(vector<Appointment>& appointments)
{
	ofstream file("appointments.txt");
	for(auto& a:appointments)
	{
		file<<a.appointmentId<<","<<a.patientId<<","<<a.doctorId<<","<<a.appointmentDate<<","<<a.appointmentTime<<endl;
	}
	file.close();
}
vector<Appointment> loadAllAppointments()
{
	vector<Appointment>appointments;
	ifstream file("appointments.txt");
	string line;
	while(getline(file,line))
	{
		if(line.empty())
		{
			continue;
		}
		Appointment a;
		stringstream ss(line);
		string appointmentIdStr,pIdStr,dIdStr;
		
		getline(ss,appointmentIdStr,',');
		getline(ss,pIdStr,',');
		getline(ss,dIdStr,',');
		getline(ss,a.appointmentDate,',');
		getline(ss,a.appointmentTime,',');
		
		a.appointmentId=stoi(appointmentIdStr);
		a.patientId=stoi(pIdStr);
		a.doctorId=stoi(dIdStr);
		appointments.push_back(a);
		if(a.appointmentId>=nextAppointmentId)
		{
			nextAppointmentId=a.appointmentId+1;
		}
	}
	file.close();
	return appointments;
}
//loadalldoctors and savealldoctors function
vector<Doctor>loadAllDoctors()
{
	vector<Doctor>doctors;
	ifstream file("doctors.txt");
	string line;
	while(getline(file,line))
	{
		if(line.empty())
		{
			continue;
		}
		Doctor d;
		stringstream ss(line);
		string doctorIdStr;
		
		getline(ss,doctorIdStr,','); 
		getline(ss,d.doctorName,',');  
		getline(ss,d.specialization,','); 
		getline(ss,d.status,',');
		getline(ss,d.contactNo,','); 
		
		d.doctorId=stoi(doctorIdStr);
		
		doctors.push_back(d);
		if(d.doctorId>=nextDoctorId)
		{
			nextDoctorId=d.doctorId+1;
		}
	}
	file.close();
	return doctors;
}

void saveAllDoctors(vector<Doctor>& doctors)
{
	ofstream file("doctors.txt");
	for(auto& d:doctors)
	{
		file<<d.doctorId<<","<<d.doctorName<<","<<d.specialization<<","<<d.status<<","<<d.contactNo<<endl;
	}
	file.close();
}

//loadallpatients and saveallpatients are outside the class 	because work with many patients at a time 
vector<Patient>loadAllPatients()
{
	vector<Patient>patients;
	ifstream file("patients.txt");
	string line; //it will read each line one by one througl while loop
	while(getline(file,line))
	{
		if(line.empty())
		{
			continue;
		}
		Patient p; //p is object of patient class
		stringstream ss(line); //stringstream will break the line and ss is an object of stringstream
		string idStr,ageStr; //these will be string and later converted to int 
		
		getline(ss,idStr,','); 
		getline(ss,p.patientName,','); 
		getline(ss,ageStr,','); 
		getline(ss,p.gender,','); 
		getline(ss,p.diagnosis,',');
		getline(ss,p.contactNo,','); 
		
		p.patientId=stoi(idStr);
		p.age=stoi(ageStr);
		
		
		patients.push_back(p);
		if(p.patientId>=nextPatientId)
		{
			nextPatientId=p.patientId+1;//this is to start the ids from wehere it left
		}
	}
	file.close();
	return patients;
}
void saveAllPatients(vector<Patient>& patients)
{
	ofstream file("patients.txt");
	for(auto& p:patients)
	{
		file<<p.patientId<<","<<p.patientName<<","<<p.age<<","<<p.gender<<","<<p.diagnosis<<","<<p.contactNo<<endl;
	}
	file.close();
}

//

//Patient Managemeny Menu
void patientManagementMenu()
{
	int choice;
	while(true)
	{
		cout<<"\n-----Patient Management Menu-----"<<endl;
		cout<<"1. Add Patient"<<endl;
		cout<<"2. Update Patient"<<endl;
		cout<<"3. View Patients"<<endl;
		cout<<"4. Search Patient"<<endl;
		cout<<"5. Back to Main Menu"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				Patient temp;
				temp.addPatient();
				break;
			}
			case 2:{
				Patient::updatePatient();
				break;
			}
			case 3:{
				Patient::viewPatients();
				break;
			}
			case 4:{
				Patient::searchPatient();
				break;
			}
			case 5:{
				cout<<"\nReturning to Main Menu...\n";
				return;
			}
			default: 
			cout<<"Invalid choice! Please try again.\n";
		}
	}
}

//Doctor Managemeny Menu
void doctorManagementMenu()
{
	int choice;
	while(true)
	{
		cout<<"\n-----Doctor Management Menu-----"<<endl;
		cout<<"1. Add Doctor"<<endl;
		cout<<"2. Update Doctor"<<endl;
		cout<<"3. View Doctors"<<endl;
		cout<<"4. Search Doctor"<<endl;
		cout<<"5. Update Doctor Status"<<endl;
		cout<<"6. Back to Main Menu"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				Doctor temp;
				temp.addDoctor();
				break;
			}
			case 2:{
				Doctor::updateDoctor();
				break;
			}
			case 3:{
				Doctor::viewDoctors();
				break;
			}
			case 4:{
				Doctor::searchDoctor();
				break;
			}
			case 5:{
				Doctor::updateDoctorStatus();
				break;
			}
			case 6:{
				cout<<"\nReturning to Main Menu...\n";
				return;
			}
			default: 
			cout<<"Invalid choice! Please try again.\n";
		}
	}
}

void appointmentManagementMenu()
{
	int choice;
	while(true)
	{
		cout<<"\n-----Appointment Management Menu-----"<<endl;
		cout<<"1. Book Appointment"<<endl;
		cout<<"2. Reschedule Appointment"<<endl;
		cout<<"3. View Appointments"<<endl;
		cout<<"4. Search Appointment"<<endl;
		cout<<"5. Back to Main Menu"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				Appointment temp;
				temp.bookAppointment();
				break;
			}
			case 2:{
				Appointment::rescheduleAppointment();
				break;
			}
			case 3:{
				Appointment::viewAppointments();
				break;
			}
			case 4:{
				Appointment::searchAppointment();
				break;
			}
			case 5:{
				cout<<"\nReturning to Main Menu...\n";
				return;
			}
			default: 
			cout<<"Invalid choice! Please try again.\n";
		}
	}
}

void billManagementMenu()
{
	int choice;
	while(true)
	{
		cout<<"\n------ Bill Management Menu -------\n";
		cout<<"1. Generate Bill"<<endl;
		cout<<"2. View Bills"<<endl;
		cout<<"3. Search Bill"<<endl;
		cout<<"4. Back to Main Menu"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:{
				Bill temp;
				temp.generateBill();
				break;
			}
			case 2:{
				Bill::viewBills();
				break;
			}
			case 3:{
				Bill::searchBill();
				break;
			}
			case 4:{
				cout<<"\nReturning to Main Menu...\n";
				return;
			}
			default: 
			cout<<"Invalid choice! Please try again.\n";
		}
	}
}

void mainMenu()
{
	int choice;
	while(true)
	{
		cout<<"\n------ Hospital Management System -------\n";
		cout<<"1. Manage Patients"<<endl;
		cout<<"2. Manage Doctors"<<endl;
		cout<<"3. Manage Appointments"<<endl;
		cout<<"4. Manage Billing"<<endl;
		cout<<"5. Exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
			case 1:
				patientManagementMenu();
				break;
			case 2:
				doctorManagementMenu();
				break;
			case 3: 
				appointmentManagementMenu();
				break;
			case 4:
				billManagementMenu();
				break;
			case 5:
				cout<<"Thank you for using Hospital Management System!"<<endl;
				return;
			default:
				cout<<"Invalid choice!"<<endl;
		}
	}
}

int main()
{
	allPatients=loadAllPatients();
	allDoctors=loadAllDoctors();
	allAppointments=loadAllAppointments();
	allBills=loadAllBills();
	cout<<"Hospital Management System is working"<<endl;
	mainMenu();
	return 0;
}