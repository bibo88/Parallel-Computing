 
 // to trexeis me thn entolh gcc -o t openmp2_prim.c -lm -fopenmp


 
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 1000


int N;
int num; //einai o ari8mos tou thread pou trexoume kai 8elv na einai global metablhth gia na to blepoun kai mesa sthn thread fun
int V[sizeof(int)];//kratame se auton ton pinaka tis korufes tou apotelesmatos afou efarmosoyme ton prim,dld tis korufes tou dendrou pou 8a prokupsei apo to upografhma.(me bash panta ton algori8mo poy mas deinei h askhsh)
int **a;//einai o pinakas ston opoio apo8hkeuetai to arxiko grafhma.mias kai to grafhma einai mh dieu8hnomeno mporoume na anaparasthsoum ton pinaka me enan anw trigwniko,me thn timh 3000 sthn kuria diagwnia.H timh auth sumbolizei sto programma mas to apeiro mias kai den uparxei periptwsh na uparxei pleura pou na kateu8hnetai ston eauto ths.
int **E; //aftos o pinakas krataei ths akmes poy 8eloyme me ta mikrotera barh gia ton algori8mo tou prim.Sto telos dhladh 8a katalhksoume sto dendro pou 8a katalhgame logo tou prim.


struct edge{  //domh h opoia krataei ta stoixeia pou xreiazomaste gia ka8e akomh,dld tis 2 korufes pou sundeontai mesw ths akmhs
               //kai to baros ths.
int i;
int j;
int value;
};

struct edge  *last,*spot;//diktes sthn domh edge.o last 8a xrhsimopoih8ei gia tis akmes pou 8a enwsoun ta dendra pou 8a epistrafoun apo tis thread_fun,enw o spot 8a krataei ta stoixeia pou prepei na perastoun san parametroi sthn thread_fun.


int main(void)
 {
 
 int g,p;
 int count;//metrhths wste na kseroume poses akmes 8a prepei na sugkrinoume wste na broume thn mikroterh kai na thn pros8esoume sto sunolo me ths akmes.
 
count=0;

 int num7,h,b;
 int s,d;//flags gia na elegksoume an gia thn akmh (u,v) to u brisketai sto sunolo V  enw to v den anhkei akoma sto sunolo auto.
 s=0;//autes einai oi times gia tis opoies h akmh den mporei na mpei sto sunolo V.
 d=1;//to epi8ymhto einai s=1 kai d=1.
   
	int n;
	srand(time(NULL));
	int r;//sthn metablhth auth kratame thn stroggulopoihmenh pros ta panw timh ths diaireshs N/n pou orizei poses korufes 8a anate8oun se ka8e thread kata gia thn klhsh tou thread function
	int i,j,k,f;//to f to xrhsimopoiw gia na apo8hkeuw ka8e fora to euros tou upopinaka sthn periptwsh if(!((r*n)==N)) ka8ws allazei sunarthsh tou m. 
	int temp;//to xrhsimopoiw gia na pouhkeuw to deikth sthn domh last wste na mporw meta na to prospelasw
	f=0;
	int m=0;//to m einai to akeraio upoloipo ths diaireshs N/n otan auth den diaireitai akribws.
	int min=3000;
	printf("enter the number of threads:\n");
	scanf("%d",&n);
	printf("Give the dimensions of the matrix(N,M):\n");
	scanf("%d",&N);// to N einai iso me to M kai iso me ton ari8mo twn korufwn tou grafhmatos.
	int v[N];//einai o monodiastatos pinakas ston opoio apo8hkeuw thn arxikh korufh apo thn opoia 8elv na arxisei ka8e thread thn prospelash toy arxikou pinaka. 	
        int l=0;//deikthw gia na prispelaunei ton pinaka v
        last=(struct edge *)calloc(4,sizeof(struct edge));
	spot=(struct edge *)calloc(4,sizeof(struct edge));
      struct edge *begin; //deikths sthn domh edge.xrhsimopoieitai ws pinakas eggrafwn ths domhs.
 begin=malloc((N*(N-1)/2)*sizeof(struct edge));

//dhmiourgia tou arxikou pinaka a,kai arxikopoihsh tou me bash thn askhsh.

        a = malloc(N * sizeof(int *));
	if (a == NULL)
	   {
	     puts("\nFailure to allocate room for i pointers.\n");
	     exit(0);
	   }


	for (i =0; i<N; i++)
	    {
	        a[i] = malloc(N * sizeof(int));
        	if (a[i] == NULL)
        	   {
			printf("\nFailure to allocate for i[%d]\n",i);
			exit(0);
        	   }
    	    }


	a[0][1]=1;
	a[0][2]=3;
	a[0][3]=5;
	a[0][4]=6;
	a[0][5]=8;
	a[0][6]=10;
	a[0][7]=1;
	a[1][4]=3;
	a[1][5]=5;
	a[1][6]=9;
	a[1][7]=13;
	a[1][2]=6;
	a[1][3]=4;
	a[2][3]=2;
	a[2][4]=1;
	a[2][5]=6;
	a[2][6]=5;
	a[2][7]=10;
	a[3][4]=23;
	a[3][5]=11;
	a[3][6]=45;
	a[3][7]=15;
	a[4][5]=9;
	a[4][6]=7;
	a[4][7]=5;
	a[5][6]=11;
	a[5][7]=3;
	a[6][7]=15;
	

	for (i=0; i<N; i++)
		for (j=0; j<i; j++)
			a[i][j]=a[j][i];
			
	for(i=0; i<N; i++)
	        a[i][i]=3000;		
			
    	printf("\no pinakas geitniashs arxika\n");
	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
			printf("%d\t",a[i][j]);
	         printf("\n");
	}		
         
//dhmiourgia kai arxikopoihsh tou telikou dendrou
	E = malloc(N * sizeof(int *));
		if (E == NULL)
		  {
		   puts("\nFailure to allocate room for i pointers.\n");
		   exit(0);
		  }


	for (i =0; i<N; i++)
	    {
	        E[i] = malloc(N * sizeof(int));
        	if (E[i] == NULL)
        	   {
			printf("\nFailure to allocate for i[%d]\n",i);
			exit(0);
        	   }
    	    }
        printf("akolou8ei to dendro\n");
	
       for (i=0; i<N; i++)
           {	
             for (j=0; j<N; j++)
		{
		E[i][j]=3000; //arxika to sunolo twn akmwn einai keno.
               // printf("%d\t",E[i][j]);
                }
       printf("\n");
     }

       printf("akolou8ei o pinakas V\n");
 for(i=0;i<N;i++) 
    {
      V[i]=3000;
      //printf("%d\n",V[i]);
    } 
    for(i=0;i<N;i++)
         {
           last[i].value=3000;
           last[i].i=3000;
           last[i].j=3000;
           //printf("to begin%d->value einai %d\n",i,begin[i].value);
         }

   
       r=floor(N/n);
     //  printf("to r einai %d\n",r);
       V[0]=0;

  //parakatw brisketai o kwdikas pou ekteleitai sthn periptwsh pou o ari8mos twn thread diaireitai akribws me ton ari8mo twn korufwn.opote kai ka8e thread 8a analabei akribws ton idio ari8mo korufwn.elpizw prin apo thn paradwsh na brw enan tropo na ektelei ston idio kwdika kai sthn periptwsh pou den diaireitai akribws.
       
       if((r*n)==N)
         {
       while(V[N-1]==3000)   //edw o elegxos einai gia oso to V[4] einai iso me 3000.otan auto pernei kapoia allh timh to loop 8a prepei na stamataei.
   {
          for (num=0; num<n; num++)
              {
	        v[num]=num*r;//sto v i apo8hkeuw thn korufh apo thn apoia 8a arxisei to vhma i na epeksergazetai to arxiko grafhma mesw ths thread function.to bhma tou upografhmatos gia ka8e thread einai edw standard kai iso me r,se anti8esh me thn allh periptwsh. 
	   
	        spot->i=v[num];
	        spot->j=r;
	        spot->value = num;      
	       // printf("oi times pou 8a metafer8oun einai %d kai %d.\n",spot->i,spot->j);		 
	       // pthread_create( &a_thread[num],NULL, (void *)&thread_fan, (void *)spot);  
	       
/////////EDW MPAINEI TO PARALLHLO TMHMA GIA OPENMP @@@@@@@@@@@@
  
  #pragma omp parallel shared(h,b,spot,a,begin,count,V,num7,last,min) private(i,j) num_threads(n)
 {
//se ayton ton pinaka 8a apo8hkeusw tis times twn akmwn pou mporoun na mpoun sto E.auth pou 8a mpei 8a einai h megalyterh.to mege8ow autou tou pinaka einai (N^2-N)/2.edw den exoume akoma balei dunamiko N ,h timh einai 5,opote 8a balw opou xreiastw to mege8ow autou tou pinaka : 10.(opws px grammh 96)
 h=spot->i;
 b=spot->j;
 num7 = spot->value;

 #pragma omp sections nowait
{
//int l;//einai metrhths gia na kserw se poia 8esh tou pinaka 8a mpei ka8e korufh pou pros8etw sto V.
 //l=0;
// #pragma omp parallel  num_threads(n) 
 
	// #pragma omp flush()
#pragma omp section
{	
 printf("\no pinakas a pou perna san orisma, arxika\n");
 for (i=0; i<N; i++)
     {
       for (j=h; j<h+b; j++)
	    printf("%d\t",a[i][j]);
       printf("\n");
       
     }	 
}
#pragma omp section
{	
//#pragma omp for schedule(static)
      for(i=0;i<b*(b-1)/2;i++)
         {
           begin[i].value=4000;
           begin[i].i=4000;
           begin[i].j=4000;
           
         }

 }
 //*******************************otan exw dhmiourghsei ton pinaka V me dunamiko tropo h timh tou epirreazetai apo to parapanw for kai to V[0] deixnei 3000.parola auta to for xreiazetai gia to programma.otan pali to orizw statika sthn periptwsh pou to thread einai 1 petaei segmentation fault otan mpainei sto while.
        #pragma omp section
    {
         for (j=h; j<h+b; j++)
        {    
           for (i=0; i<N; i++)
                
                { 
                //gia ka8e mia akmh pou den einai 3000 8a elegksw an plhpoi ths prohpo8eseiw wste na mpei sto E
                  if(a[j][i]!=3000) //ta exw balei anapoda giati 8elw na ta prospelasw kata sthles kai oxi kata grammes
                     {  
                       for(k=0;k<N;k++)
                         {   
                           if(V[k]==j) //ean h mia akrh ths pleuras brisketai sto sunolo V tote kanoume thn shmaia s->1 kai stamatame to psaksimo sto V.
                             { 
                               s=1;
                        
                               break;
                             } 
                         }
                
          
                
                     //edw psaknoyme na doume ean h allh korufh ths akmhs brisketai sto sunolo V.emeis den 8eloume na brisketai edw dld to d 8eloume 
                   //na einai 1.
                         for(k=0;k<N;k++)
                            { 
                              if(V[k]==i)   //ean brisketai kai h allh korufh ths    akmhs sto sunolo V kanoume to d=0 
                                {
                                 d=0;
                                }                
                             }   
              
                         if(s==1 && d==1) 
                           { 
                             count++;//metrame poses akmes exoun thn mia tous korufh sto V enw thn allh oxi,wste na mporesoume meta na tis sugkrinoume kai na broume poia einai h mikroterh wste na thn pros8esoume sto sunolo E.
                             //printf("h akmh (%d,%d)mporei na mpei sto sunolo\n",i,j);
                
                             begin[count].value=a[j][i];//oles oi akmes autou tou tupou apo8hkeuontai sthn domh now ari8mhmenes.
                             begin[count].i=j;
                             begin[count].j=i;
                         
                           }         
                       s=0;//ksanaarxikopoiw ta flags gia thn epomenh akmh poy 8a elegksw an plhroi tis prohpo8eseis na mpei sto sunolo E
                       d=1;
                   }//telos if
            }
        }
       }// section end 
 //prin loipon ananewsoume to V me mia kainourgia korufh apo tis akmes pou metrhsame parapanw dialegoume thn mikroterh kai thn pros8etoume sto E.epeita ananewnoume to V.
#pragma omp section
{
 for(i=1;i<=count;i++)
    {
      if(begin[i].value<min) 
        {
         min=begin[i].value;
         p=begin[i].i;
         g=begin[i].j;
        }   
    }
 

 last[num7].i=p;
 last[num7].j=g;
 last[num7].value=min;
 printf("h mikroterh akmh exei timh %d\n",last[num7].value);
 
 count=0; //ksanamhdenizw to count mias kai 8a xreiastei lofw tou while loop na ksanpsaksw gia thn mikroterh akmh mono pou twra einai ananewmeno to V me mia akoma korufh.
 min=3000;
 //tellos parallel

 }
 }// sections end
      }//parallel end
}//for end
#pragma omp barrier

//#pragma omp single	  

	  for (i=0; i<n; i++)
              {  printf("to last[%d] einai %d\n",i,last[i].value);
	        if(last[i].value<=min)    
	           {
	           
	           min=last[i].value;
	           
	           temp=i;
	           } 
	       }      
	         printf("to mikrotero globaly einai %d\n",min);
	         E[last[temp].i][last[temp].j]=min;
	         //efoson bre8hke kapoio mikrotero 8a prepei na pros8esoume thn akmh pou den anhkei hdh sto v sto parapanw sunolo.
	         l++;
	         
	         V[l]=last[temp].j;
	         
	         ///diagrafoume thn antistoixh akmh apo ton arxiko pinaka ka8ws epishw kai thn summetrikh ths.
	         a[last[temp].i][last[temp].j]=3000;
	         a[last[temp].j][last[temp].i]=3000;
	         
	         //edw ka8arizw ton pinaka anakoinwsewn twn akmwn.
	         for (i=0; i<n; i++)
	             {
	             last[i].value=3000;
            	     last[i].i=3000;
           	     last[i].j=3000;
	             } 

	    min=3000;
	}//telos tou while         
     }//TELOS tou prwtou if
    
        
   
    
          if(!((r*n)==N))
            {
       
              m=N%n;
              //printf("to m einai % d\n",m); 
 while(V[N-1]==3000)   //edw o elegxos einai gia oso to V[4] einai iso me 3000.otan auto pernei kapoia allh timh to loop 8a prepei na stamataei.
   { 
    
              for(num=0; num<n; num++)
                 {          
         
         //h idea einai ta m prwta upografhmata na exoun kata mia parapanw korufh dld r+1 enw ta upoloipa upografhmata exoun r korufes.   
         
                  if(num<m)
                   {
                     v[num]=num*(r+1);//edw to bhma den einai opws prin ana r korufes alla ana r+1 korufes.auth h epipleon korufh proerxetai apo to m dld diamoirazoume tis epipleon m korufes mia mia sta upografhmata.
	             spot->i=v[num];
	             spot->j=r+1;
	             spot->value=num;      
	            // printf("oi times pou 8a metafer8oun einai %d kai %d.\n",spot->i,spot->j);   
	            //&&&&&&&&&&&&&& pthread_create( &a_thread[num],NULL, (void *)&thread_fan, (void *)spot);
                 
              /////////EDW MPAINEI TO PARALLHLO TMHMA GIA OPENMP @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
              
              
    #pragma omp parallel shared(h,b,spot,a,begin,count,V,num7,last,min) private(i,j) num_threads(n)
 {
 #pragma omp sections nowait
{          
              
//se ayton ton pinaka 8a apo8hkeusw tis times twn akmwn pou mporoun na mpoun sto E.auth pou 8a mpei 8a einai h megalyterh.to mege8ow autou tou pinaka einai (N^2-N)/2.edw den exoume akoma balei dunamiko N ,h timh einai 5,opote 8a balw opou xreiastw to mege8ow autou tou pinaka : 10.(opws px grammh 96)
 h=spot->i;
 b=spot->j;
 num7 = spot->value;
 

 
//#pragma omp parallel  num_threads(n) 
 #pragma omp section
 {
 printf("\no pinakas a pou perna san orisma, arxika\n");
 for (i=0; i<N; i++)
     {
       for (j=h; j<h+b; j++)
	    printf("%d\t",a[i][j]);
       printf("\n");
       
     }	 
}
#pragma omp section
{
//#pragma omp for schedule(static)
      for(i=0;i<b*(b-1)/2;i++)
         {
           begin[i].value=4000;
           begin[i].i=4000;
           begin[i].j=4000;
           
         }
}
 //*******************************otan exw dhmiourghsei ton pinaka V me dunamiko tropo h timh tou epirreazetai apo to parapanw for kai to V[0] deixnei 3000.parola auta to for xreiazetai gia to programma.otan pali to orizw statika sthn periptwsh pou to thread einai 1 petaei segmentation fault otan mpainei sto while.
#pragma omp section
{        
         for (j=h; j<h+b; j++)
        {    
           for (i=0; i<N; i++)
                
                { 
                //gia ka8e mia akmh pou den einai 3000 8a elegksw an plhpoi ths prohpo8eseiw wste na mpei sto E
                  if(a[j][i]!=3000) //ta exw balei anapoda giati 8elw na ta prospelasw kata sthles kai oxi kata grammes
                     {  
                       for(k=0;k<N;k++)
                         {   
                           if(V[k]==j) //ean h mia akrh ths pleuras brisketai sto sunolo V tote kanoume thn shmaia s->1 kai stamatame to psaksimo sto V.
                             { 
                               s=1;
                        
                               break;
                             } 
                         }
                
          
                
                     //edw psaknoyme na doume ean h allh korufh ths akmhs brisketai sto sunolo V.emeis den 8eloume na brisketai edw dld to d 8eloume 
                   //na einai 1.
                         for(k=0;k<N;k++)
                            { 
                              if(V[k]==i)   //ean brisketai kai h allh korufh ths    akmhs sto sunolo V kanoume to d=0 
                                {
                                 d=0;
                                }                
                             }   
              
                         if(s==1 && d==1) 
                           { 
                             count++;//metrame poses akmes exoun thn mia tous korufh sto V enw thn allh oxi,wste na mporesoume meta na tis sugkrinoume kai na broume poia einai h mikroterh wste na thn pros8esoume sto sunolo E.
                             //printf("h akmh (%d,%d)mporei na mpei sto sunolo\n",i,j);
                
                             begin[count].value=a[j][i];//oles oi akmes autou tou tupou apo8hkeuontai sthn domh now ari8mhmenes.
                             begin[count].i=j;
                             begin[count].j=i;
                         
                           }         
                       s=0;//ksanaarxikopoiw ta flags gia thn epomenh akmh poy 8a elegksw an plhroi tis prohpo8eseis na mpei sto sunolo E
                       d=1;
                   }//telos if
            }
        }
        }// section end 
 //prin loipon ananewsoume to V me mia kainourgia korufh apo tis akmes pou metrhsame parapanw dialegoume thn mikroterh kai thn pros8etoume sto E.epeita ananewnoume to V.
#pragma omp section
{
 for(i=1;i<=count;i++)
    {
      if(begin[i].value<min) 
        {
         min=begin[i].value;
         p=begin[i].i;
         g=begin[i].j;
        }   
    }
 
 last[num7].i=p;
 last[num7].j=g;
 last[num7].value=min;
 //printf("h mikroterh akmh exei timh %d\n",last[num7].value);
 
 count=0; //ksanamhdenizw to count mias kai 8a xreiastei lofw tou while loop na ksanpsaksw gia thn mikroterh akmh mono pou twra einai ananewmeno to V me mia akoma korufh.
 min=3000;   
 }
 
 //parallel telos
                 }// sections end
                 }// parallel end
                 }//if end
                 
                
                 
#pragma omp barrier 
                 if(num==m) //epidh apo edw kai mpros 8a allaksei to bhma ths prospelashs tou upopinaka grafoume ksexwrista thn periptwsh pou i=m.     
                   {   
                     v[num]=v[num-1]+r+1;
	             spot->i=v[num];
                     spot->j=r;
                     spot->value=num;      
	             printf("oi times pou 8a metafer8oun einai %d kai %d.\n",spot->i,spot->j);//stis 8eseis twn upopinakwn ston arxiko pinaka antika8hstw me 3000 gia na mou einai pio eukolo meta na brw thn mikroterh akmh pou sundeei tous pinakes pou epistrefontai apo thn thread fun.	 
                       
                  
                  
                  
                  /////////EDW MPAINEI TO PARALLHLO TMHMA GIA OPENMP @@@@@@@@@@@@
                  
      #pragma omp parallel shared(h,b,spot,a,begin,count,V,num7,last,min) private(i,j) num_threads(n)
 {
 #pragma omp sections nowait
{                 
                  
//se ayton ton pinaka 8a apo8hkeusw tis times twn akmwn pou mporoun na mpoun sto E.auth pou 8a mpei 8a einai h megalyterh.to mege8ow autou tou pinaka einai (N^2-N)/2.edw den exoume akoma balei dunamiko N ,h timh einai 5,opote 8a balw opou xreiastw to mege8ow autou tou pinaka : 10.(opws px grammh 96)
 h=spot->i;
 b=spot->j;
 num7 = spot->value;
 
//int l;//einai metrhths gia na kserw se poia 8esh tou pinaka 8a mpei ka8e korufh pou pros8etw sto V.
 //l=0;
 
//#pragma omp parallel  num_threads(n) 
#pragma omp section 
{
 printf("\no pinakas a pou perna san orisma, arxika\n");
 for (i=0; i<N; i++)
     {
       for (j=h; j<h+b; j++)
	    printf("%d\t",a[i][j]);
       printf("\n");
       
     }	 
}
//#pragma omp for schedule(static)
#pragma omp section
{
      for(i=0;i<b*(b-1)/2;i++)
         {
           begin[i].value=4000;
           begin[i].i=4000;
           begin[i].j=4000;
           
         }
}
 //*******************************otan exw dhmiourghsei ton pinaka V me dunamiko tropo h timh tou epirreazetai apo to parapanw for kai to V[0] deixnei 3000.parola auta to for xreiazetai gia to programma.otan pali to orizw statika sthn periptwsh pou to thread einai 1 petaei segmentation fault otan mpainei sto while.
#pragma omp section
{        
         for (j=h; j<h+b; j++)
        {    
           for (i=0; i<N; i++)
                
                { 
                //gia ka8e mia akmh pou den einai 3000 8a elegksw an plhpoi ths prohpo8eseiw wste na mpei sto E
                  if(a[j][i]!=3000) //ta exw balei anapoda giati 8elw na ta prospelasw kata sthles kai oxi kata grammes
                     {  
                       for(k=0;k<N;k++)
                         {   
                           if(V[k]==j) //ean h mia akrh ths pleuras brisketai sto sunolo V tote kanoume thn shmaia s->1 kai stamatame to psaksimo sto V.
                             { 
                               s=1;
                        
                               break;
                             } 
                         }
                
          
                
                     //edw psaknoyme na doume ean h allh korufh ths akmhs brisketai sto sunolo V.emeis den 8eloume na brisketai edw dld to d 8eloume 
                   //na einai 1.
                         for(k=0;k<N;k++)
                            { 
                              if(V[k]==i)   //ean brisketai kai h allh korufh ths    akmhs sto sunolo V kanoume to d=0 
                                {
                                 d=0;
                                }                
                             }   
              
                         if(s==1 && d==1) 
                           { 
                             count++;//metrame poses akmes exoun thn mia tous korufh sto V enw thn allh oxi,wste na mporesoume meta na tis sugkrinoume kai na broume poia einai h mikroterh wste na thn pros8esoume sto sunolo E.
                            // printf("h akmh (%d,%d)mporei na mpei sto sunolo\n",i,j);
                
                             begin[count].value=a[j][i];//oles oi akmes autou tou tupou apo8hkeuontai sthn domh now ari8mhmenes.
                             begin[count].i=j;
                             begin[count].j=i;
                         
                           }         
                       s=0;//ksanaarxikopoiw ta flags gia thn epomenh akmh poy 8a elegksw an plhroi tis prohpo8eseis na mpei sto sunolo E
                       d=1;
                   }//telos if
            }
        }
        } // end section 
 //prin loipon ananewsoume to V me mia kainourgia korufh apo tis akmes pou metrhsame parapanw dialegoume thn mikroterh kai thn pros8etoume sto E.epeita ananewnoume to V.
#pragma omp section
{
 for(i=1;i<=count;i++)
    {
      if(begin[i].value<min) 
        {
         min=begin[i].value;
         p=begin[i].i;
         g=begin[i].j;
        }   
    }

 last[num7].i=p;
 last[num7].j=g;
 last[num7].value=min;
// printf("h mikroterh akmh exei timh %d\n",last[num7].value);
 
 count=0; //ksanamhdenizw to count mias kai 8a xreiastei lofw tou while loop na ksanpsaksw gia thn mikroterh akmh mono pou twra einai ananewmeno to V me mia akoma korufh.
 min=3000;
}          //parallel telos        
                // EDW TELEIWNEI TO PARALLHLO  KOMMATIIIII ####################   
   }// end sections
   }// end parallel
   }            // end if   
                  
  #pragma omp barrier                 
     
                if(num>m)              
                  {
                    v[num]=v[num-1]+r;
	            spot->i=v[num];
	            spot->j=r;
	            spot->value=num;      
	            printf("oi times pou 8a metafer8oun einai %d kai %d.\n",spot->i,spot->j); 
		    //&&&&&&&&&pthread_create( &a_thread[num],NULL, (void *)&thread_fan, (void *)spot);
               	   
               	 
               	 
              //parallhlia
               	 
          #pragma omp parallel shared(h,b,spot,a,begin,count,V,num7,last,min) private(i,j) num_threads(n)
 {
 #pragma omp sections nowait
{          	 
               	 
               	 
//se ayton ton pinaka 8a apo8hkeusw tis times twn akmwn pou mporoun na mpoun sto E.auth pou 8a mpei 8a einai h megalyterh.to mege8ow autou tou pinaka einai (N^2-N)/2.edw den exoume akoma balei dunamiko N ,h timh einai 5,opote 8a balw opou xreiastw to mege8ow autou tou pinaka : 10.(opws px grammh 96)
 h=spot->i;
 b=spot->j;
 num7 = spot->value;
 
//int l;//einai metrhths gia na kserw se poia 8esh tou pinaka 8a mpei ka8e korufh pou pros8etw sto V.
 //l=0;
 
//#pragma omp parallel  num_threads(n) 
#pragma omp section 
{
 printf("\no pinakas a pou perna san orisma, arxika\n");
 for (i=0; i<N; i++)
     {
       for (j=h; j<h+b; j++)
	    printf("%d\t",a[i][j]);
       printf("\n");
       
     }	 
}
//#pragma omp for schedule(static)
#pragma omp section
{
      for(i=0;i<b*(b-1)/2;i++)
         {
           begin[i].value=4000;
           begin[i].i=4000;
           begin[i].j=4000;
           
         }

 //*******************************otan exw dhmiourghsei ton pinaka V me dunamiko tropo h timh tou epirreazetai apo to parapanw for kai to V[0] deixnei 3000.parola auta to for xreiazetai gia to programma.otan pali to orizw statika sthn periptwsh pou to thread einai 1 petaei segmentation fault otan mpainei sto while.
}
#pragma omp section 
{        
         for (j=h; j<h+b; j++)
        {    
           for (i=0; i<N; i++)
                
                { 
                //gia ka8e mia akmh pou den einai 3000 8a elegksw an plhpoi ths prohpo8eseiw wste na mpei sto E
                  if(a[j][i]!=3000) //ta exw balei anapoda giati 8elw na ta prospelasw kata sthles kai oxi kata grammes
                     {  
                       for(k=0;k<N;k++)
                         {   
                           if(V[k]==j) //ean h mia akrh ths pleuras brisketai sto sunolo V tote kanoume thn shmaia s->1 kai stamatame to psaksimo sto V.
                             { 
                               s=1;
                        
                               break;
                             } 
                         }
                
          
                
                     //edw psaknoyme na doume ean h allh korufh ths akmhs brisketai sto sunolo V.emeis den 8eloume na brisketai edw dld to d 8eloume 
                   //na einai 1.
                         for(k=0;k<N;k++)
                            { 
                              if(V[k]==i)   //ean brisketai kai h allh korufh ths    akmhs sto sunolo V kanoume to d=0 
                                {
                                 d=0;
                                }                
                             }   
              
                         if(s==1 && d==1) 
                           { 
                             count++;//metrame poses akmes exoun thn mia tous korufh sto V enw thn allh oxi,wste na mporesoume meta na tis sugkrinoume kai na broume poia einai h mikroterh wste na thn pros8esoume sto sunolo E.
                            // printf("h akmh (%d,%d)mporei na mpei sto sunolo\n",i,j);
                
                             begin[count].value=a[j][i];//oles oi akmes autou tou tupou apo8hkeuontai sthn domh now ari8mhmenes.
                             begin[count].i=j;
                             begin[count].j=i;
                         
                           }         
                       s=0;//ksanaarxikopoiw ta flags gia thn epomenh akmh poy 8a elegksw an plhroi tis prohpo8eseis na mpei sto sunolo E
                       d=1;
                   }//telos if
            }
        } 
 //prin loipon ananewsoume to V me mia kainourgia korufh apo tis akmes pou metrhsame parapanw dialegoume thn mikroterh kai thn pros8etoume sto E.epeita ananewnoume to V.
}// end section
#pragma omp section
{
 for(i=1;i<=count;i++)
    {
      if(begin[i].value<min) 
        {
         min=begin[i].value;
         p=begin[i].i;
         g=begin[i].j;
        }   
    }
 
 last[num7].i=p;
 last[num7].j=g;
 last[num7].value=min;
// printf("h mikroterh akmh exei timh %d\n",last[num7].value);
 
 count=0; //ksanamhdenizw to count mias kai 8a xreiastei lofw tou while loop na ksanpsaksw gia thn mikroterh akmh mono pou twra einai ananewmeno to V me mia akoma korufh.
 min=3000;  
}               	//parallel telos
 }// sections end
 }// parallel end              	
               	
               	  // EDW TELEIWNEI TO PARALLHLO  KOMMATIIIII ####################  
               	   
               	   }// if end
 #pragma omp barrier       
                 }//edw kleinei to for
         for (i=0; i<n; i++)
              { //printf("to last[%d] einai %d\n",i,last[i].value);
	        if(last[i].value<=min)    
	           {
	           
	           min=last[i].value;
	           temp=i;
	           } 
	       }      
	        // printf("to mikrotero globaly einai %d\n",min);
	         E[last[temp].i][last[temp].j]=min;
	         //efoson bre8hke kapoio mikrotero 8a prepei na pros8esoume thn akmh pou den anhkei hdh sto v sto parapanw sunolo.
	         l++;

	         V[l]=last[temp].j;
	         
	         ///diagrafoume thn antistoixh akmh apo ton arxiko pinaka ka8ws epishw kai thn summetrikh ths.
	         a[last[temp].i][last[temp].j]=3000;
	         a[last[temp].j][last[temp].i]=3000;
	         
	         //edw ka8arizw ton pinaka anakoinwsewn twn akmwn.
	         for (i=0; i<n; i++)
	             {
	             last[i].value=3000;
            	     last[i].i=3000;
           	     last[i].j=3000;
	             } 
	         min=3000;    
           }//edw kleinei while       
             
        }//edw kleinei to if
    
     for (i=0; i<N; i++)
     {	
        for (j=0; j<N; j++)
                printf("%d\t",E[i][j]);
        printf("\n");
     }		
   		
    	
return 0;
 }



