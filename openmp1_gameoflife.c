

 
//to teliko programma gia to game of life.o kwdikas autos ginetai compile me thn entolh gcc -o t openmp1_gameoflife.c -lm -fopenmp.

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000


//void  thread_fan(void *); //to prototupo ths sunarthshs pou kalei to thread
int x,y,N,M;//x,y einai oi telikes metablhtes(to bhma) me bash tis opoies 8a
//prospelasoun ta thread ton pinaka.opws kai oi diastaseis tou pinaka(N,M)einai global metablhtes kai prepei na ths blepei kai h thread fun

//pthread_barrier_t bar;

struct coo{        //h domh auth xrhsimopoieitai gia na deinei tis suntetagmenes enos stoixeiou ka8ws kai ws to tetarto orisma ths thread function,kai einai to shmeio apo to opoio arxizei h thread fun na epeksergazetai ton arxiko pinaka.
	int i;
	int j;
};

int **rowptr; //me thn boh8eia twn deiktwn autwn dhmiourgoume kai epeksergazomaste ston arxiko pinaka pou periexei to gameoflife.o deuteros deikths xrhsimopoieitai gia ton boh8htiko pinaka pou xrhsimopoioume gia thn antigrafei twn pinakwn.
int **rowptr2;


int main(void){

	int n;//einai o ari8mos twn thread.
	int k,l;
	double m,g,s;
	int i,num,min,j,f; 
	int temp;
	int r[sizeof(int)]; //oi duo auth pinakes kratane tis times olwn twn ari8mwn pou apoteloun zeugos ginomenou tou n.
	int c[sizeof(int)];
        int index; //deikths o opoios xrhsimopoieitai gia thn ari8mhsh twn threads.
        index = 0;

	printf("enter the number of threads:\n");
	scanf("%d",&n);
	printf("Give the dimensions of the matrix(N,M):\n");
	scanf("%d,%d",&N,&M);
	
	struct coo begin, *now; //deikths sthn domh coo
	now = &begin;
	#pragma omp barrier
	/*pthread_t   a_thread[MAX]; //orizoume kai dhmiourgoume twn pinaka nhmatwn pou 8a xreiastoume gia thn ektelesh twn upopinakwn pou 8a dhmiourghsoume.

*/
//sto parakatw kommati kwdika desmeuoume xwro dunamika gia ton disdiastato pinaka pou antiproswpeuei to gameof life.
//frontizoume ean o pinakas pou 8elei na dhmiourgsei o xrhsth einai mege8ous NxN na dhmiourghsoume ena pinaka (N+2)x(N+2).me auton ton tropo kai 8etontas to epipleon "plaisio" kapoia mh epitrepth timh (diaforh tou 1,0) mporoume na epeksergastoume swsta ta stoixeia tou pinaka ws pros ta geitonika tous.

	rowptr = malloc((N+2) * sizeof(int *));
	if (rowptr == NULL)
	  {
	   puts("\nFailure to allocate room for i pointers.\n");
	   exit(0);
	  }


	for (i =0; i<N+2; i++)
	    {
	        rowptr[i] = malloc((M+2) * sizeof(int));
        	if (rowptr[i] == NULL)
        	   {
			printf("\nFailure to allocate for i[%d]\n",i);
			exit(0);
        	   }
    	    }
	
/* Edw vazoume arxikes times sto 1o stigmiotypo toy provlimatos.TODO    egw exw balei proswrina thn timh 1 se ola ta stoixeia tou pinaka.fantazomai oti mia random me 0 kai 1 8a douleuei kala gia to sugkekrimeno problhma.	*/
for (i = 1; i < N+1; i++)
		for (j = 1; j < M+1; j++)
			rowptr[i][j]=0;
        
	
	

for(i=1; i<N+1; i++)
rowptr[i][1]=1;
for(j=1; j<M+1; j++)
rowptr[N][j]=1;	
for(i=1; i<N+1; i++)
rowptr[i][M]=1;	

         for(i=0;i<N+2;i++)
	   {
	    for(j=0;j<M+2;j++)
 		 if(i==0 || i==N+1 || j==0 || j==M+1)
 		    rowptr[i][j]=3;
	   }

	printf("\no pinakas rowptr arxika\n");
	for (i=0; i<N+2; i++)
           {
	     for (j=0; j<M+2; j++)
		 printf("%d\t",rowptr[i][j]);
	     printf("\n");
           }


//dhmiourgoume kai ton deutero pinaka me ton idio tropo mono pou einai kenos.8a ton xreiastoume parakatw kata thn antigrafh twn 2 pinakwn.
        rowptr2 = malloc((N+2) * sizeof(int *));
	if (rowptr2 == NULL)
    	  {
        	puts("\nFailure to allocate room for i pointers.\n");
		exit(0);
    	  }


	for (i = 0; i < N+2; i++)
    	  {
        	rowptr2[i] = malloc((M+2) * sizeof(int));
        	if (rowptr2[i] == NULL)
        	   {
 			printf("\nFailure to allocate for i[%d]\n",i);
 			exit(0);
        	   }
	  }

	

	for (i = 1; i < N+1; i++)
		for (j = 1; j < M+1; j++)
			rowptr2[i][j]=0;
        
        for(i=0;i<N+2;i++)
       	   {
 		for(j=0;j<M+2;j++)
			if(i==0 || i==N+1 || j==0 || j==M+1)
		rowptr2[i][j]=3;
	  }
//parakatw,briskoume ola ta zeugh ginomenwn tou ari8mou twn thread xrhsimopoiwntas thn riza tou ari8mou.epita 8a epileksoume ekeino to zeugari ginomenwn pou exei thn mikroterh diafora kata apoluth timh kai 8a xrhsimopoihsoume tis times autou tou ginomenou wste na prokupsoun ta bhmata x,y me ta opoia 8a prospelaunetai o arxikos pinakas wste na xwristei se upopinakes.


	m = sqrt(n);

	for(i=1; i<=m; i++)
	   {
	     num=n/i;
	     if(num*i==n)  
	       {
		r[i]=i;
		c[i]=num;

	//	printf("o ari8mos %d exei ws ginomeno ta zeugh \t %d,%d\n",n,r[i],c[i]);
	       }
	    }

	min=n;//8etoume ws min thn timh n giati einai h megaluterh timh pou mporei na parei h diafora twn ginomenwn tou n.
	
	for(i=1;i<=m;i++)
	   {
	     if(r[i]!=0)
	       {
			temp=r[i]-c[i];
			temp=abs(temp);
			if(temp<=min)
			{
				min=temp;
				j=i;
			}
		}
	   }
	//printf("to min einai:%d\n",min);
	
	if(r[j]>c[j]){   //8eloume h megaluterh timh apo to zeugos ginomenwn pou exoume epileksei na antistoixizetai sthn metablhth g dld opws fainetai parakatw sthn x.
		g=r[j];
 		s=c[j];
	}
	else{	
		s=r[j];
 		g=c[j];
	}
	//printf("ta g kai s einai:%f %f\n",g,s);
	//printf("ta N kai M einai:%d %d\n",N,M);

       //opws fainetai parakatw kratame ton kontinotero megalutero akeraio ths prakshs N/g opws kai ths M/s kai autes apo8hkeuoume stis metablhtes x,y.me auton ton tropo uparxei periptwsh kapoio thread na xreiastei na prospeasei megalutero upopinaka (me bash tis metablhtes x,y) apo ton pragmatiko upopinaka pou exei prokupsei logo tou diaxwrismou tou arxikou pinaka se kommatia.auto den 8a apotelesei problhma giati to thread mporei na blepei ton pragmatiko upopinaka "gemismeno" omws me epipleon kenes grammes kai sthles wste na exei to idio mege8os me ton upopinaka pou tou exei anate8ei.
	x=ceil(N/g);
	y=ceil(M/s);
	//printf("ta x kai y einai:%d %d\n",x,y);


//parakatw brisketai o kwdikas me ton opoio epilegoume to arxiko stoixeio(panw deksia) ka8e upopinaka me bash to bhma x kai y.h orizontia suntetagmenh k allazei sunexws ana x enw gia na allaksei h ka8eth suntetagmenh l (ana y) 8a prepei to k%N==0 sthn peiptwsh pou to k kai N diairountai akribws h k%(N+1)==0 sthn periptwsh pou den diairountai akribws.auto praktika sumbainei otan to k exei "diatreksei" me bhma x thn grammh tou pinaka sthn opoia brisketai kai 8elei na allaksei grammh.oi times tou stoixeiou pou prokuptei k,l 8a auksh8oun kata ena mias kai o telikos pinakas exei suntetagmenes N+2xNx2,enw emeis exoume brei tis suntetagmenes gia stoixeia ton pinaka NxN.to stoixeio auto loipon einai to tetarto orisma ths thread function kai me bash auto kai sumfwna me to bhma x,y to thread 8a epeksergastei ton upopinaka.
	
	
	// 100 FASEIS
        for(f=0;f<100;f++)
	   {
            printf("\t\tEIMASTE STHN %d FASH\n",f);	   
	    l=-y;
	    for(k=0;;k+=x)
	       { 
		if((k%(N+(N%2)))==0)
		  {
	 		l=l+y;
	 		
	 	  }
	
		rowptr[k][l]=2;//to exw balei etsi gia na blepw ean briskomaste sto swsto shmeio
		now->i = k+1; 
		now->j = l+1;
	       //printf("\t\t\t Thread Fan parameters\n\t\t\tk is %d and l is %d\n", k,l);
    
	         int count=0;
 		 int h=now->i;
 		 int t=now->j;
	         printf("oi suntetagmenes %d %d\n",h,t);
		
		#pragma omp parallel for default(none) num_threads(n)\
				shared(h,t,rowptr,count,rowptr2,x,y) private(i,j)
		 
           ///////// parallel
		 	
for(i=h;i<x+h;i++)
   {	
     for(j=t;j<y+t;j++)
	{  
	if(rowptr[i][j]==0)    //an ena nekro stoixeio exei akribws 3 zwntanous  geitones,zwntaneueu kai to idio
		{
		count=0;
		if(rowptr[i-1][j-1]==1) count+=1;
		if(rowptr[i-1][j]==1) count+=1;
		if(rowptr[i-1][j+1]==1) count+=1;
		if(rowptr[i][j-1]==1) count+=1;
		if(rowptr[i][j+1]==1) count+=1;
		if(rowptr[i+1][j-1]==1) count+=1;
		if(rowptr[i+1][j]==1) count+=1;
		if(rowptr[i+1][j+1]==1) count+=1;		

                if(count==3) 	{
                rowptr2[i][j]=1; 
                		}
                
                }
	if(rowptr[i][j]==1)
		{
		count=0;
		if(rowptr[i-1][j-1]==1) count+=1;
		if(rowptr[i-1][j]==1) count+=1;
		if(rowptr[i-1][j+1]==1) count+=1;
		if(rowptr[i][j-1]==1) count+=1;
		if(rowptr[i][j+1]==1) count+=1;
		if(rowptr[i+1][j-1]==1) count+=1;
		if(rowptr[i+1][j]==1) count+=1;
		if(rowptr[i+1][j+1]==1) count+=1;
                
                if(count<2) rowptr2[i][j]=0;
		if(count>3) rowptr2[i][j]=0;
		if((count==2) ||(count==3)) rowptr2[i][j]=1;

		}

	}
   }	  
   	   //#pragma omp flush(h,t,count)   
     #pragma omp flush(h,t,count)
	     #pragma omp barrier 
      //telos toy parallel tmhmatos
	
	   index++;    
               if((k==(N+(N%2)-x))&&(l==(M+(M%2)-y))) // Edw elegxoume an ftasame sto katw deksia stoixeio tou pinaka.
	       break;    

	      
              }
     
     
       for (i=0; i<N+2; i++)
	   for (j=0; j<M+2; j++)                              
 	       rowptr[i][j]=rowptr2[i][j];
 		 
       printf("\no pinakas rowptr meta thn antigrafh-TELOS FASHS %d\n",f);
       for (i=0; i<N+2; i++)
          {
	   for (j=0; j<M+2; j++)
	       printf("%d\t",rowptr[i][j]);
	   printf("\n");
          }

        }


return 0;

}



