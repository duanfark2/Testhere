#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include <stdlib.h>
using namespace std;
class items
{ int itemno,batchno,empno,noofunits,noofunun;
  char itemname[40];
  float bp,sppu,profit;
  public:
  void in(int itemnoin,int empnoin,int noofunitsin,float countryin,float bpin
  ,float sppuin);
  int itemnoret()
  { return itemno;
  }
  int batchnoret()
  { return batchno;
  }
  int empnoret()
  { return empno;
  }
  int noofunitsret()
  { return noofunits;
  }
  int noofununret()
  { return noofunun;
  }
  char* itemnameret()
  { return itemname;
  }
  float sppuret()
  { return sppu;
  }
  void decnoun()
  { --noofunun;
  }
  void incnoun()
  { ++noofunun;
  }
  void viewitemse(float country,char *currency)
  { cout<<"Item number:\t"<<itemno<<endl;
    cout<<"Item name:\t";
    puts(itemname);
    cout<<"Batch number:\t"<<batchno<<endl;
    cout<<"Employee number of the employee who added this batch to the";
    cout<<" stock:\t"<<empno<<endl;
    cout<<"Number of units of this batch:\t"<<noofunits<<endl;
    cout<<"Number of unsold units of this batch:\t"<<noofunun<<endl;
    cout<<"Bulk price of this batch in:\t";
    puts(currency);
    cout<<"\b "<<bp/country<<endl;
    cout<<"Selling price per unit for this batch in:\t";
    puts(currency);
    cout<<"\b "<<sppu/country<<endl;
    cout<<"Profit per piece for this batch:\t";
    puts(currency);
    cout<<"\b "<<profit/country<<endl;
  }
  void viewitemsc(float country,char *currency)
  { cout<<"Item number:\t"<<itemno<<endl;
    cout<<"Item name:\t";
    puts(itemname);
    cout<<"Batch number:\t"<<batchno<<endl;
    cout<<"Number of unsold units of this batch:\t"<<noofunun<<endl;
    cout<<"Selling price per unit for this batch:\t";
    puts(currency);
    cout<<"\b "<<sppu/country<<endl;
  }
};
void items::in(int itemnoin,int empnoin,int noofunitsin,float countryin
,float bpin,float sppuin)
{ char internalch='n';
  itemno=itemnoin;
  empno=empnoin;
  noofunits=noofunitsin;
  noofunun=noofunits;
  bp=bpin*countryin;
  sppu=sppuin*countryin;
  ifstream fi;
  items i;
  fi.open("items.dat",ios::binary);
  do
  { batchno=1;
    if((internalch=='y')||(internalch=='Y'))
    { cout<<"Enter item number\n";
      cin>>itemno;
    }
    while(fi)
    { if(itemno==i.itemnoret())
      { batchno=i.batchnoret()+1;
	strcpy(itemname,i.itemnameret());
	cout<<"The name for this item is\n";
	puts(itemname);
	cout<<"Enter 'y' or 'Y' if this name is correct for the item you ";
	cout<<"are adding to the stock\nOterwise enter any other ";
	cout<<"character\n";
	cin>>internalch;
	break;
      }
    }
  }while((internalch=='y')||(internalch=='Y'));
  fi.close();
  if(batchno==1)
  { cout<<"Enter the name for this item\n";
    gets(itemname);
  }
  profit=sppu-bp/noofunits;
}
class persondet
{ protected:
  float country;//exchange rate w.r.t. USD(1 unit of currency=country USD)
  char currency[10],name[50],address[80],phone[13],pass[22];
  void persondetin()
  { gets(name);
    gets(address);
    gets(phone);
    gets(pass);
    cin>>country;
    gets(currency);
  }
  void persondetout()
  { puts(name);
    puts(address);
    puts(phone);
    cout<<country<<endl;
    puts(currency);
  }
  public:
  char *passret()
  { return(pass);
  }
  float countryret()
  { return(country);
  }
  char *currencyret()
  { return(currency);
  }
};
class emp:public persondet
{ int empno;
  float profit;
  public:
  emp()
  { profit=0;
  }
  void in()
  { cout<<"Enter name, address, phone number(without any spaces,- or /), ";
    cout<<"password(a maximum of 20 characters), worth of one unit of ";
    cout<<"the country's currency in USD and its symbol/short form\n";
    ifstream fi;
    fi.open("emp.dat",ios::binary);
    fi.seekg(0,ios::end);
    empno=1+fi.tellg()/sizeof(emp);
    fi.close();
    persondetin();
    cout<<"The assigned employee number is\n"<<empno<<endl;
  }
  void out()
  { cout<<"The employee number, name, address, phone number, worth of one ";
    cout<<"unit of the country's currency in USD, its symbol/short form ";
    cout<<"and profit are:\n";
    cout<<empno<<endl;
    persondetout();
    cout<<profit<<endl;
  }
  void editprofit(float cp,float sp,int noofunits);
  void ats();
  int empnoret()
  { return(empno);
  }
  float profitret()
  { return(profit);
  }
};
void emp::editprofit(float cp,float sp,int noofunits)
{ int noalex=0;
  items i;
  ifstream fi;
  fi.open("items.dat",ios::binary);
  fi.read((char*)&i,sizeof(i));
  do
  { if(i.empnoret()==empno)
    noalex+=i.noofunitsret();
    fi.read((char*)&i,sizeof(i));
  }while(fi);
  fi.close();
  profit=(noalex*profit+noofunits*(cp-sp))/(noalex+noofunits);
}
void emp::ats()
{ int itemnoin,noofunitsin;
  float bpin,sppuin;
  items i;
  ofstream fo;
  cout<<"Enter the item number, number of units, bulk price and selling ";
  cout<<"price per unit\n";
  cin>>itemnoin>>noofunitsin>>bpin>>sppuin;
  i.in(itemnoin,empno,noofunitsin,country,bpin,sppuin);
  fo.open("items.dat",ios::binary|ios::app);
  fo.write((char*)&i,sizeof(i));
  fo.close();
  cout<<"Item has been added to the stock\n";
  editprofit(bpin/noofunitsin,sppuin,noofunitsin);
  cout<<"The Profit you have made for the company has been updated\n";
  cout<<"It's current value is\t"<<profit*100<<"%\n";
}
struct carts
{ int itemno,custno,batchno;
  carts *prev,*next;
  carts()
  { prev=NULL;
    next=NULL;
  }
}*cartstart=NULL,*cartlast=NULL,*tempcart=NULL;
class cust:public persondet
{ int custno;
  char creditcno[22];
  public:
  void in()
  { cout<<"Enter your name, address, phone ";
    cout<<"number(without any spaces,- or /), ";
    cout<<"password(a maximum of 20 characters), worth of one unit of your ";
    cout<<"country's currency in USD, its symbol/short form and your credit ";
    cout<<"card number\n";
    ifstream fi;
    fi.open("cust.dat",ios::binary);
    fi.seekg(0,ios::end);
    custno=1+fi.tellg()/sizeof(cust);
    fi.close();
    persondetin();
    gets(creditcno);
    cout<<"The assigned customer number is\n"<<custno<<endl;
  }
  void out()
  { cout<<"The customer number, name, address, phone number, worth of one ";
    cout<<"unit of their country's currency in USD and its symbol/short ";
    cout<<"form are:\n";
    cout<<custno<<endl;
    persondetout();
  }
  void atc(int itemno);
  void searchcart(int itemno);
  void rfc(int itemno);
  void emptycart();
  int custnoret()
  { return custno;
  }
};
void cust::atc(int itemno)
{ int avf=0;
  fstream f;
  items i;
  f.open("items.dat",ios::binary|ios::in|ios::out);
  while(f)
  { f.read((char*)&i,sizeof(i));
    if((i.itemnoret()==itemno)&&(i.noofununret()>0))
    { if(cartstart==NULL)
      { cartstart=new carts;
	cartlast=cartstart;
      }
      else
      { tempcart=new carts;
	tempcart->next=cartstart;
	cartstart->prev=tempcart;
	cartstart=tempcart;
      }
      cartstart->itemno=itemno;
      cartstart->custno=custno;
      cartstart->batchno=i.batchnoret();
      i.decnoun();
      f.seekp(f.tellg()-sizeof(i));
      f.write((char*)&i,sizeof(i));
      avf=1;
      break;
    }
  }
  f.close();
  if(avf==0)
  { cout<<"Could not add the requested item to cart(the item number";
    cout<<" entered might be invalid or the requested item might have gone";
    cout<<" out of stock)\n";
  }
  else
  cout<<"Item added to cart successfylly\n";
}
void cust::searchcart(int itemno)
{ tempcart=cartlast;
  while((tempcart->itemno!=itemno)&&(tempcart!=NULL))
  tempcart=tempcart->prev;
  if(tempcart!=NULL)
  cout<<"Item found\n";
  else
  cout<<"Item not found\n";
}
void cust::rfc(int itemno)
{ items i;
  fstream f;
  searchcart(itemno);
  if(tempcart==NULL)
  { cout<<"There are no items(in all or of the given item number) to be ";
    cout<<"deleted\n";
  }
  else
  { f.open("items.dat",ios::binary|ios::in|ios::out);
    while(f)
    { f.read((char*)&i,sizeof(i));
      if((i.itemnoret()==tempcart->itemno)
      &&(i.batchnoret()==tempcart->batchno))
      { i.incnoun();
	f.seekp(f.tellg()-sizeof(i));
	f.write((char*)&i,sizeof(i));
	break;
      }
    }
    f.close();
    if(cartstart==cartlast)
    delete tempcart;
    else if(tempcart==cartstart)
    { cartstart=cartstart->next;
      cartstart->prev=NULL;
      delete tempcart;
    }
    else if(tempcart==cartlast)
    { cartlast=cartlast->prev;
      cartlast->next=NULL;
      delete tempcart;
    }
    else
    { tempcart->prev->next=tempcart->next;
      tempcart->next->prev=tempcart->prev;
      delete tempcart;
    }
  }
}
void cust::emptycart()
{ items i;
  tempcart=cartstart;
  while(tempcart!=NULL)
  { fstream f;
    f.open("items.dat",ios::binary|ios::in|ios::out);
    while(f)
    { f.read((char*)&i,sizeof(i));
      if((i.itemnoret()==tempcart->itemno)
      &&(i.batchnoret()==tempcart->batchno))
      { i.incnoun();
	f.seekp(f.tellg()-sizeof(i));
	f.write((char*)&i,sizeof(i));
	break;
      }
    }
    f.close();
    if(cartstart==cartlast)
    delete tempcart;
    else
    { cartstart=cartstart->next;
      cartstart->prev=NULL;
      delete tempcart;
    }
    tempcart=cartstart;
  }
  cout<<"The cart has been emptied\n";
}
void passin(char *check)
{ int i=0,j;
  system("cls");
  cout<<"Enter password\n";
  do
  { check[i]=getch();
    if((i>0)&&(check[i]=='\b'))
    { system("cls");
      cout<<"Enter password\n";
      i--;
      for(j=0;j<i;j++)
      cout<<'*';
    }
    else if(check[i]==13)//13 is the ASCII code for *enter*
    { check[i]='\0';
      i++;
      system("cls");
    }
    else
    { cout<<'*';
      i++;
    }
  }while(((i<20)&&(check[i-1]!='\0'))||(i==0));
}
int main()
{ char pass1[22];
  int ch1,ch2,ecn,ccn,icn,flag1;
  float sum;
  emp e1;
  cust c1;
  items i1;
  carts *cs=NULL,*cl=NULL,*ct=NULL;
  ifstream fi;
  ofstream fo;
  lb1:
  system("cls");
  cout<<"Welcome to Loot Lo Enterprises\n";
  getch();
  cout<<"Enter 1 if you are an employee\n";
  cout<<"      2 if you are a customer\n";
  cout<<"      3 to exit\n";
  cin>>ch1;
  system("cls");
  switch(ch1)
  { case 1 : cout<<"Enter 1 if a new employee account is to be ";
	     cout<<"created(administrator password required)\n";
	     cout<<"      2 if a pre-existing employee account has to be ";
	     cout<<"accessed\n";
	     cout<<"      3 to return to the main menu\n";
	     cin>>ch1;
	     lb2:
	     system("cls");
	     switch(ch1)
	     { case 1 : passin(pass1);
			if(!strcmp(pass1,"")) //add admin password here
			{ e1.in();
			  fo.open("emp.dat",ios::binary|ios::app);
			  fo.write((char*)&e1,sizeof(e1));
			  fo.close();
			  cout<<"New employee account added\n";
			}
			else
			cout<<"Incorrect password\n";
			getch();
			goto lb1;
	       case 2 : flag1=0;
			cout<<"Enter your employee number\n";
			cin>>ecn;
			fi.open("emp.dat",ios::binary|ios::in);
			while(fi)
			{ fi.read((char*)&e1,sizeof(e1));
			  if(ecn==e1.empnoret())
			  { flag1=1;
			    break;
			  }
			}
			fi.close();
			if(flag1==0)
			{ cout<<"Nonexistent employee number\n";
			  cout<<"Enter 1 to re-enter employee number\n";
			  cout<<"      2 to go back to main menu\n";
			  cout<<"      3 to exit\n";
			  cin>>ch2;
			  switch(ch2)
			  { case 1 : goto lb2;
			    case 3 : goto lb7;
			    default : goto lb1;
			  }
			}
			passin(pass1);
			if(!strcmp(pass1,e1.passret()))
			{ lb3:
			  system("cls");
			  cout<<"Enter 1 to view the details for all items\n";
			  cout<<"      2 to view the details for every";
			  cout<<" item you have added to the stock\n";
			  cout<<"      3 to add new stock\n";
			  cout<<"      4 to view the account details of all";
			  cout<<" customers\n";
			  cout<<"      5 to view the account details of any";
			  cout<<" specific customer(customer number of that";
			  cout<<" customer is required)\n";
			  cout<<"      6 to view the total percentage";
			  cout<<" profit you have made for the company\n";
			  cout<<"      7 to view your own account details\n";
			  cout<<"      8 to return to main menu\n";
			  cout<<"      9 to exit\n";
			  cin>>ch1;
			  lb4:
			  system("cls");
			  switch(ch1)
			  { case 1 : fi.open("items.dat",ios::binary|ios::in);
				     fi.read((char*)&i1,sizeof(i1));
				     do
				     { i1.viewitemse(e1.countryret()
				       ,e1.currencyret());
				       cout<<"Enter any character to";
				       cout<<" proceed\n";
				       getch();
				       fi.read((char*)&i1,sizeof(i1));
				     }while(fi);
				     fi.close();
				     goto lb3;
			    case 2 : fi.open("items.dat",ios::binary|ios::in);
				     fi.read((char*)&i1,sizeof(i1));
				     do
				     { if(i1.empnoret()==e1.empnoret())
				       { i1.viewitemse(e1.countryret()
					 ,e1.currencyret());
					 cout<<"Enter any character to";
					 cout<<" proceed\n";
					 getch();
					 fi.read((char*)&i1,sizeof(i1));
				       }
				     }while(fi);
				     fi.close();
				     goto lb3;
			    case 3 : e1.ats();
				     getch();
				     goto lb3;
			    case 4 : fi.open("cust.dat",ios::binary|ios::in);
				     fi.read((char*)&c1,sizeof(c1));
				     do
				     { c1.out();
				       cout<<"Enter any character to";
				       cout<<" proceed\n";
				       getch();
				       fi.read((char*)&c1,sizeof(c1));
				     }while(fi);
				     fi.close();
				     goto lb3;
			    case 5 : flag1=0;
				     cout<<"Enter the customer number of the";
				     cout<<" customer whose details you want";
				     cout<<" to see\n";
				     cin>>ccn;
				     fi.open("cust.dat",ios::binary|ios::in);
				     while(fi)
				     { fi.read((char*)&c1,sizeof(c1));
				       if(ccn==c1.custnoret())
				       { flag1=1;
					 break;
				       }
				     }
				     fi.close();
				     if(flag1==0)
				     { cout<<"Nonexistent customer number\n";
				       cout<<"Enter 1 to re-enter customer";
				       cout<<" number\n";
				       cout<<"      2 to go back to previous";
				       cout<<" menu\n";
				       cout<<"      3 to go back to the main";
				       cout<<" menu\n";
				       cin>>ch2;
				       switch(ch2)
				       { case 1 : goto lb4;
					 case 3 : goto lb1;
					 default : goto lb3;
				       }
				     }
				     c1.out();
				     cout<<"Enter any character to proceed\n";
				     getch();
				     goto lb3;
			    case 6 : cout<<"The total percentage";
				     cout<<" profit you have made for";
				     cout<<" the company is\n";
				     cout<<e1.profitret()<<endl;
				     getch();
				     goto lb3;
			    case 7 : e1.out();
				     getch();
				     goto lb3;
			    case 8 : goto lb1;
			    case 9 : goto lb7;
			    default : goto lb3;
			  }
			}
			else
			{ cout<<"Incorect password\n";
			  getch();
			  goto lb1;
			}
	       default : goto lb1;
	     }
    case 2 : cout<<"Enter 1 if you want to create a new customer account\n";
	     cout<<"      2 if you want to lag into your pre-existing ";
	     cout<<"account\n";
	     cout<<"      3 to return to the main menu\n";
	     cin>>ch1;
	     lb5:
	     system("cls");
	     switch(ch1)
	     { case 1 : c1.in();
			fo.open("cust.dat",ios::binary|ios::app);
			fo.write((char*)&c1,sizeof(c1));
			fo.close();
			cout<<"New customer account added\n";
			getch();
			goto lb1;
	       case 2 : flag1=0;
			cout<<"Enter your customer number\n";
			cin>>ccn;
			fi.open("cust.dat",ios::binary|ios::in);
			while(fi)
			{ fi.read((char*)&c1,sizeof(c1));
			  if(ccn==c1.custnoret())
			  { flag1=1;
			    break;
			  }
			}
			fi.close();
			if(flag1==0)
			{ cout<<"Nonexistent customer number\n";
			  cout<<"Enter 1 to re-enter customer number\n";
			  cout<<"      2 to go back to main menu\n";
			  cout<<"      3 to exit\n";
			  cin>>ch2;
			  switch(ch2)
			  { case 1 : goto lb5;
			    case 3 : goto lb7;
			    default : goto lb1;
			  }
			}
			passin(pass1);
			if(!strcmp(pass1,c1.passret()))
			{ lb6:
			  system("cls");
			  cout<<"Enter 1 to view the details for all items\n";
			  cout<<"      2 to add an item to your cart(item";
			  cout<<" number of that item is required)\n";
			  cout<<"      3 to remove an item from your";
			  cout<<" cart(item number of that item is";
			  cout<<" required)\n";
			  cout<<"      4 to view all items in your cart\n";
			  cout<<"      5 to find a specific item in your";
			  cout<<" cart(item number of that item is";
			  cout<<" required)\n";
			  cout<<"      6 to view the total price of your";
			  cout<<" cart\n";
			  cout<<"      7 to purchase all the items in your";
			  cout<<" cart\n";
			  cout<<"      8 to empty your cart without";
			  cout<<" purchasing the items in it\n";
			  cout<<"      9 to view the item numbers and batch";
			  cout<<" numbers of all the items that you have";
			  cout<<" ever purchased\n";
			  cout<<"      10 to view your own account details\n";
			  cout<<"      11 to return to main menu\n";
			  cout<<"      12 to exit\n";
			  cin>>ch1;
			  system("cls");
			  switch(ch1)
			  { case 1 : fi.open("items.dat",ios::binary|ios::in);
				     fi.read((char*)&i1,sizeof(i1));
				     do
				     { if(i1.noofununret()>0)
				       { if((cs==cl)&&(cs==NULL))
					 { cs=new carts;
					   cs->itemno=i1.itemnoret();
					   cl=cs;
					   i1.viewitemsc(c1.countryret()
					   ,c1.currencyret());
					 }
					 else
					 { flag1=0;
					   ct=cs;
					   while(ct!=NULL)
					   { if(i1.itemnoret()==ct->itemno)
					     { flag1=1;
					       break;
					     }
					     ct=ct->next;
					   }
					   if(flag1==1)
					   { fi.read((char*)&i1,sizeof(i1));
					     continue;
					   }
					   else
					   { ct=new carts;
					     ct->itemno=i1.itemnoret();
					     ct->next=cs;
					     cs=ct;
					     i1.viewitemsc(c1.countryret()
					     ,c1.currencyret());
					   }
					 }
				       }
				       fi.read((char*)&i1,sizeof(i1));
				       cout<<"Enter any character to";
				       cout<<" proceed\n";
				       getch();
				     }while(fi);
				     fi.close();
				     ct=cs;
				     while(ct!=NULL)
				     { cs=cs->next;
				       delete ct;
				       ct=cs;
				     }
				     goto lb6;
			    case 2 : cout<<"Enter the item number of the";
				     cout<<" item you want to add to cart\n";
				     cin>>icn;
				     c1.atc(icn);
				     getch();
				     goto lb6;
			    case 3 : cout<<"Enter the item number of the";
				     cout<<" item you want to remove from";
				     cout<<" cart\n";
				     cin>>icn;
				     c1.rfc(icn);
				     getch();
				     goto lb6;
			    case 4 : fi.open("items.dat",ios::binary|ios::in);
				     tempcart=cartstart;
				     while(tempcart!=NULL)
				     { fi.read((char*)&i1,sizeof(i1));
				       do
				       { if((tempcart->itemno==i1.itemnoret())
					 &&
					 (tempcart->batchno==i1.batchnoret()))
					 { i1.viewitemsc(c1.countryret()
					   ,c1.currencyret());
					   cout<<"Enter any character to";
					   cout<<" proceed\n";
					   getch();
					   break;
					 }
					 fi.read((char*)&i1,sizeof(i1));
				       }while(fi);
				       fi.seekg(0);
				       tempcart=tempcart->next;
				     }
				     fi.close();
				     goto lb6;
			    case 5 : cout<<"Enter the item number of the";
				     cout<<" item you want to find\n";
				     cin>>icn;
				     c1.searchcart(icn);
				     if(tempcart!=NULL)
				     { fi.open("items.dat"
				       ,ios::binary|ios::in);
				       fi.read((char*)&i1,sizeof(i1));
				       do
				       { if((tempcart->itemno==i1.itemnoret())
					 &&
					 (tempcart->batchno==i1.batchnoret()))
					 { i1.viewitemsc(c1.countryret()
					   ,c1.currencyret());
					   cout<<"Enter any character to";
					   cout<<" proceed\n";
					   getch();
					   break;
					 }
					 fi.read((char*)&i1,sizeof(i1));
				       }while(fi);
				       fi.close();
				     }
				     goto lb6;
			    case 6 : sum=0;
				     fi.open("items.dat",ios::binary|ios::in);
				     tempcart=cartstart;
				     while(tempcart!=NULL)
				     { fi.read((char*)&i1,sizeof(i1));
				       do
				       { if((tempcart->itemno==i1.itemnoret())
					 &&
					 (tempcart->batchno==i1.batchnoret()))
					 { sum+=i1.sppuret();
					   break;
					 }
					 fi.read((char*)&i1,sizeof(i1));
				       }while(fi);
				       fi.seekg(0);
				       tempcart=tempcart->next;
				     }
				     fi.close();
				     cout<<"The total price of your cart";
				     cout<<" is\n"<<sum;
				     getch();
				     goto lb6;
			    case 7 : sum=0;
				     fo.open("sold.dat",ios::binary|ios::app);
				     fi.open("items.dat",ios::binary|ios::in);
				     tempcart=cartstart;
				     while(tempcart!=NULL)
				     { fi.read((char*)&i1,sizeof(i1));
				       do
				       { if((tempcart->itemno==i1.itemnoret())
					 &&
					 (tempcart->batchno==i1.batchnoret()))
					 { fo.write((char*)tempcart
					   ,sizeof(*tempcart));
					   sum+=i1.sppuret();
					   break;
					 }
					 fi.read((char*)&i1,sizeof(i1));
				       }while(fi);
				       fi.seekg(0);
				       tempcart=tempcart->next;
				     }
				     fi.close();
				     fo.close();
				     cout<<"The total price of your cart";
				     cout<<" is\n"<<sum;
				     getch();
				     goto lb6;
			    case 8 : c1.emptycart();
				     getch();
				     goto lb6;
			    case 9 : fi.open("sold.dat",ios::binary|ios::in);
				     fi.read((char*)tempcart
				     ,sizeof(*tempcart));
				     do
				     { if(tempcart->custno==c1.custnoret())
				       { cout<<"Item number is\t";
					 cout<<tempcart->itemno<<endl;
					 cout<<"Batch number is\t";
					 cout<<tempcart->batchno<<endl;
					 cout<<"Enter any character to";
					 cout<<" proceed\n";
					 getch();
				       }
				       fi.read((char*)tempcart
				       ,sizeof(*tempcart));
				     }while(fi);
				     fi.close();
				     goto lb6;
			    case 10 : c1.out();
				      getch();
				      goto lb6;
			    case 11 : c1.emptycart();
				      goto lb6;
			    case 12 : c1.emptycart();
				      goto lb7;
			    default : goto lb6;
			  }
			}
			else
			{ cout<<"Incorect password\n";
			  getch();
			  goto lb1;
			}
	       default : goto lb1;
	     }
    case 3 : goto lb7;
    default : goto lb1;
  }
  lb7:
  system("cls");
  getch();
  return 0;
}
