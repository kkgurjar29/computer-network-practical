//stop and wait
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define inc(k) k=(k+1)%2;

using namespace std;

typedef struct
{
	int data;
}packet;

typedef struct
{
	int seq;
	int ack;
	packet *info;
}frame;

int event;
int flag = 0;
int success;
int temp = -1;
frame s;
packet buffer;
int k=0;

void from_network_layer(packet *p)
{
	s.info = p;
	s.seq = inc(k);
}

void to_physical_layer(frame *f)
{
	cout<<"\n\t\tData : "<<f->info->data;
	cout<<"\n\t\tSeq no. : "<<f->seq;
	cout<<"\n\t\tFrame sent.";
}

void from_physical_layer(frame *f)
{
	cout<<"\n\n\nRECEIVER : \tFrame	received.";
	cout<<"\n\t\tData : "<<f->info->data;
	cout<<"\n\t\tSeq no. : "<<f->seq;
	s.ack = (s.seq+1)%2;
}

void to_network_layer(packet *p)
{
	p = s.info;
}

void sender()
{
	if(flag==0)
	{
		from_network_layer(&buffer);
		cout<<"\n\n\nSENDER : \tSending Frame...";
		to_physical_layer(&s);
	}
	else if (flag==1)
	{
		cout<<"\n\n\nSENDER : \tTimeout!!! No Acknowledgement received."<<"\n\n\t\tResending Frame...";
		to_physical_layer(&s);
	}
	else
	{
		cout<<"\n\n\nSENDER : \tACK	"<<s.ack<<" received successfully.";
		success = 1;
		temp = -1;
		flag = 0;
	}

}

void receiver()
{
	event = rand()%4;
	cout<<"\n<Event "<<event<<">\n";
	if(event==0)
	{
		if (temp==s.ack)
			cout<<"\n\n\nRECEIVER : \tDuplicate	Frame Detected (FRAME DISCARDED)";
		else
		{
			from_physical_layer(&s);
			to_network_layer(&buffer);
		}
		cout<<"\n\n\t\tACK "<<s.ack<<" sent.";
		flag = 2;
	}
	else if (event==1 || event==2)
	{
		flag = 1;
	}
	else
	{
		if (temp==s.ack)
			cout<<"\n\n\nRECEIVER : \tDuplicate	Frame Detected (FRAME DISCARDED)";
		else
		{
			from_physical_layer(&s);
			to_network_layer(&buffer);
			temp = s.ack;
		}
		cout<<"\n\n\t\tACK "<<s.ack<<" sent.";
		flag = 1;
	}
	getch();
}

int main()
{
	char ans ='y';

	srand(time(NULL));
	cout<<"\nEnter data : ";
	cin>>buffer.data;
	do
	{
		success = 0;
		sender();
		Sleep(3000);
		if(!success) 
			receiver();
		else
		{
			cout<<"\n\n\nDo you want to continue (y/n) : ";
			cin>>ans;
			if(ans=='y')
			{
				cout<<"\nEnter data : ";
				cin>>buffer.data;
			}
		}
	}while(ans=='y');

	return 0;
}
