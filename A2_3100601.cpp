/***********************************************************************
Matr.-Nr:                     3100601
Nachname/Surname:             Elbehairy
Vorname/Given name:           Belal
Uni-Email:                    belal.elbehairy@stud.uni-due.de
Studiengang/Course of studis: Software Engineering
***********************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>


                using namespace std;

            void output(struct station* st);
            void output_line(struct station* first_station);
            void init (struct train &tr, string train_name, struct station* initial);
            void output(struct train* tr);
            void output_all_trains (int simulation_mins, struct train trains[], int array_legnth);
            float get_km_of_line(struct station* st,float avg_speed);

            struct station* generate_metro_line (int line_num, int num_of_stations);

                struct station
                {

                        string Name_of_the_station;
                        int minutes;
                        station *connection_option;
                        station *next= nullptr;
                        station *prev= nullptr;
                };
                struct train
                    {
                        string name_of_the_train;
                        int mins_lift;
                        bool forwrd;
                        struct station* next_station;
                    };


                int main()
                {
                    struct station* metro_line[2];
                    struct train trains[2];
                    struct station* y;
                    int simulation_mins = 0;
                    int num_of_stations1;
                    int num_of_stations2;
                    char choice;
                    int line_input;
                    int rad;
                    int line1,line2,connection_station1,connection_station2,x;
                    float avg_speed;

                    struct station* conp_station1=nullptr;
                    struct station* conp_station2=nullptr;


                    cout<<"seed value for initialisation of random number generator (try 3,5,7,...)?"<<endl;
                    cin>>rad;
                    srand(rad);

                    cout<< "input number of stations of line 1: ";
                    cin >> num_of_stations1;
                    cout<< "input number of stations of line 2: ";
                    cin >> num_of_stations2;
                    metro_line[0] = generate_metro_line(1, num_of_stations1);
                    metro_line[1] = generate_metro_line(2, num_of_stations2);

                    init(trains[0], "train 1", metro_line[0]);
                    init(trains[1], "train 2", metro_line[1]);


                    while(true){
                        cout << "e end \nl line output\nt train output\n1 simulate 1 minute"<<endl;
                        cout<<"c connection option of lines"<<endl;
                        cout<<"k total km complete outward and return ride of line"<<endl;
                        cin >> choice;
                        switch (choice)
                        {
                            case 'e':
                            return 0;
                            break;

                            case 'c':

                            cout<<"connection of which two line numbers? ";
                            cin>>line1;
                            cin>>line2;
                            if (line1==1&&line2==2 || line1==2&&line2==1) {
                            cout<<"connection at which station number of line 1? ";
                            cin>>connection_station1;
                            cout<<"connection at which station number of line 2? ";
                            cin>>connection_station2;


                            if ((line1==1&&line2==2)||(line1==2&&line2==1)) {
                                station *st1=metro_line[0];
                                station *st2=metro_line[1];
                                for (int i=1;i<connection_station1;i++){
                                    st1=st1->next;
                                }
                                for (int j=1;j<connection_station2;j++) {
                                    st2=st2->next;
                                }
                                st1->connection_option=st2;
                                st2->connection_option=st1;
                                }
                            }
                            break;

                            case 'k':
                            cout<<"which line? ";
                            cin>>line_input;
                            cout<<"average speed in km/h? ";
                            cin>>avg_speed;
                            cout<<"length of line: "<<get_km_of_line(metro_line[line_input-1],avg_speed)<<"km"<<endl;
                            break;



                            case 'l':
                            cout<< "Which line? ";
                            cin >> line_input;
                            output_line(metro_line[line_input-1]);
                            break;

                            case 't':
                            output_all_trains(simulation_mins, trains, 2);
                            break;

                            case '1':
                            simulation_mins++;
                            for(int i=0; i<2; i++){
                                if(trains[i].mins_lift==0){
                                        if((trains[i].forwrd==true && trains[i].next_station->next == nullptr)  || (trains[i].forwrd==false && trains[i].next_station->prev == nullptr)){
                                                trains[i].forwrd = !trains[i].forwrd;
                                            }
                                    if(trains[i].forwrd==true){
                                        trains[i].mins_lift = trains[i].next_station->minutes;
                                       trains[i].next_station = trains[i].next_station->next;
                                    } else if(trains[i].forwrd==false){
                                        trains[i].next_station = trains[i].next_station->prev;
                                        trains[i].mins_lift = trains[i].next_station->minutes;
                                    }

                                }else {
                                    trains[i].mins_lift--;
                                    }
                           }
                           output_all_trains(simulation_mins,trains,2);
                            break;

                        }
                    }

                }

                struct station* generate_metro_line (int line_num, int num_of_stations)
                {
                    struct station *first_station;
                    struct station *prev= nullptr;


                    for(int i=1; i<= num_of_stations; i++){
                        struct station *st= new station();
                        if (i==1){
                            first_station = st;
                        }

                        st->Name_of_the_station= "Line "+ to_string(line_num) + " station "+ to_string(i);
                        if(i==num_of_stations)
                        {
                            st->minutes = 0;
                            st->next = nullptr;
                        }
                        else
                        {
                            int time_to_next_station = (rand()%5) +1;
                            st->minutes = time_to_next_station;
                        }

                        st->prev = prev;

                        if(prev != nullptr){
                            prev->next=st;
                        }


                        prev = st;

                    }

                    return first_station;
                }

                void output(struct station* st){
                    if (st->connection_option!=nullptr) {
                        cout<<st->Name_of_the_station<<": time to next "<<st->minutes<<" mins"<<" here connection to "<<st->connection_option->Name_of_the_station<<endl;
                    }
                    else{
                     cout << st->Name_of_the_station << ": time to next: ";
                    }
                    if(st->minutes !=0)
                        cout << st->minutes<< endl;
                    else
                        cout << "End station" << endl;
                }



                void output_line(struct station* first_station){
                    struct station *current = first_station;
                    while(true){
                        output(current);
                        if(current->next != nullptr)
                            current = current->next;
                        else
                            break;
                    }
                }


                void init (struct train& tr, string train_name, struct station* initial){
                    tr.name_of_the_train= train_name;
                    tr.next_station=initial;
                    tr.mins_lift=0;
                    tr.forwrd = true;
                }

                void output(struct train* tr){
                    if (tr->mins_lift == 0){
                        cout << tr->name_of_the_train << ": Stop at "<< tr->next_station->Name_of_the_station;
                    } else {
                        cout << tr->name_of_the_train << ": "<< tr->mins_lift << " minute(s) to " << tr->next_station->Name_of_the_station;
                        if (!(tr->forwrd)){
                        cout << " (on way back)";
                    }

                    }
                    cout << endl;
                }
                void output_all_trains (int simulation_mins, struct train trains[], int array_legnth){
                    cout << "time simulation: "<< simulation_mins << " min "<< endl;
                    for (int i = 0; i < array_legnth; i++){
                        output(&trains[i]);
                    }


                }



                 float get_km_of_line(struct station* st,float avg_speed) {

                     float journey_time=0;
                     float length;
                     while (st->next!=nullptr){
                     journey_time+=((st->minutes)*2)+2;
                     st=st->next;
                     }
                     length=(avg_speed)*(journey_time/60);






                 return length;

                 }




