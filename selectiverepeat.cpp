#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

#define TOT_FRAMES 500
#define FRAMES_SEND 10

class sel_repeat
{
	private:
		int fr_send_at_instance;
		int arr[TOT_FRAMES];
		int send[FRAMES_SEND];
		int rcvd[FRAMES_SEND];
		char rcvd_ack[FRAMES_SEND];
		int sw;
		int rw; // tells expected frame
	public:
		void input();
		void sender(int);
		void reciever(int);
};

void sel_repeat :: input()
{
	int n;  // no of bits for the frame
	int m;  // no of frames from n bits

	cout << "Enter the no of bits for the sequence number ";
	cin >> n;

	m = pow (2 , n);

	int t = 0;

	fr_send_at_instance = (m / 2);

	for (int i = 0 ; i < TOT_FRAMES ; i++)
	{
	arr[i] = t;
	t = (t + 1) % m;
	}

	for (int i = 0 ; i < fr_send_at_instance ; i++)
	{
	send[i] = arr[i];
	rcvd[i] = arr[i];
	rcvd_ack[i] = 'n';
	}

	rw = sw = fr_send_at_instance;

	sender(m);
}

void sel_repeat :: sender(int m)
{
	for (int i = 0 ; i < fr_send_at_instance ; i++)
	{
		if ( rcvd_ack[i] == 'n' )
			cout << " SENDER   : Frame " << send[i] << " is sent\n";
	}
	reciever (m);
}

void sel_repeat :: reciever(int m)
{
	time_t t;
	int f;
	int f1;
	int a1;
	char ch;

	srand((unsigned) time(&t));

	for (int i = 0 ; i < fr_send_at_instance ; i++)
	{
		if (rcvd_ack[i] == 'n')
		{
			f = rand() % 10;

			// if = 5 frame is discarded for some reason
			// else frame is correctly recieved

			if (f != 5)
			{
				for (int j = 0 ; j < fr_send_at_instance ; j++){
					if (rcvd[j] == send[i])
					{
						cout << "RECIEVER : Frame " << rcvd[j] << " recieved correctly\n";
						rcvd[j] = arr[rw];
						rw = (rw + 1) % m;
						break;
					 }
				}
				if ( i == fr_send_at_instance){
					cout << "RECIEVER : Duplicate frame " << send[i] << " discarded\n";
			}
				a1 = rand() % 5;

				// if a1 == 3 then ack is lost
				// else recieved

				if (a1 == 3)
				{
					cout << "(Acknowledgement " << send[i] << " lost)\n";
					cout << " (SENDER TIMEOUTS --> RESEND THE FRAME)\n";
					rcvd_ack[i] = 'n';
				}
				else
				{
					cout << "(Acknowledgement " << send[i] << " recieved)\n";
					rcvd_ack[i] = 'p';
				}
			}
			else
			{
				int ld = rand() % 2;

				// if = 0 then frame damaged
				// else frame lost
				if (ld == 0)
				{
					cout << "RECIEVER : Frame " << send[i] << " is damaged\n";
					cout << "RECIEVER : Negative acknowledgement " << send[i]  << " sent\n";
				}
				else
				{
					cout << "RECIEVER : Frame " << send[i] << " is lost\n";
					cout << " (SENDER TIMEOUTS --> RESEND THE FRAME)\n";
				}
				rcvd_ack[i] = 'n';
			}
		}
	}

	for ( int j = 0 ; j < fr_send_at_instance ; j++)
	{
		if (rcvd_ack[j] == 'n')
		break;
	}

	int i = 0 ;
	for (int k = j ; k < fr_send_at_instance ; k++)
	{
		send[i] = send[k];

		if (rcvd_ack[k] == 'n')
		rcvd_ack[i] = 'n';
		else
		rcvd_ack[i] = 'p';

		i++;
	}

	if ( i != fr_send_at_instance )
	{
		for ( int k = i ; k < fr_send_at_instance ; k++)
		{
			send[k] = arr[sw];
			sw = (sw + 1) % m;
			rcvd_ack[k] = 'n';
		}
	}
	cout << "Want to continue...";
	cin >> ch;
	cout << "\n";

	if (ch == 'y')
		sender(m);
	else
		exit(0);
}

int main()
{
	sel_repeat sr;
	sr.input();
	getch();
}

//output
//Enter the no of bits for the sequence number 6
// SENDER   : Frame 24 is sent
// SENDER   : Frame 32 is sent
// SENDER   : Frame 32 is sent
// SENDER   : Frame 27 is sent
// SENDER   : Frame 28 is sent
// SENDER   : Frame 29 is sent
// SENDER   : Frame 30 is sent
// SENDER   : Frame 31 is sent
//RECIEVER : Frame 24 is lost
// (SENDER TIMEOUTS --> RESEND THE FRAME)
//RECIEVER : Frame 32 recieved correctly
//(Acknowledgement 32 recieved)
//RECIEVER : Frame 33 recieved correctly
//(Acknowledgement 34 recieved)
//RECIEVER : Frame 27 recieved correctly
//(Acknowledgement 34 recieved)
//RECIEVER : Frame 28 is damaged
//RECIEVER : Negative acknowledgement 28 sent
//RECIEVER : Frame 29 recieved correctly
//(Acknowledgement 35 recieved)
//RECIEVER : Frame 30 recieved correctly
//(Acknowledgement 36 lost)
// (SENDER TIMEOUTS --> RESEND THE FRAME)
//RECIEVER : Frame 31 recieved correctly
//(Acknowledgement 37 recieved)
//Want to continue...n
