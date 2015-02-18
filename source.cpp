# include <string>
# include <cstring>
# include <fstream>
# include <iostream>
using namespace std;

struct Node
{ 
	int r,c,n;
    Node* next;
};

struct stack
{
	Node* top;
    int count;
};

struct cor
{
    int r,c;
};

void push(stack* st,int row,int col,int ways) // Adds an element on the top of the stack.
{
	Node*temp=new Node;
	temp->r=row;
	temp->c=col;
	temp->n=ways;
	temp->next=st->top;
	st->top=temp;
	st->count++;
}

bool Is_Empty(stack* st)  // check if the stack is empty or not.
{
	if(st->count==0)
    return true;
    return false;
}

bool pop(stack* st) // removes the top element in the stack.
{
	if(Is_Empty(st)==true)
    return false;
	Node*temp=st->top;
	st->top=temp->next;
	delete temp;
	st->count--;
	return true;
}

void destroy_stack(stack* st) // removes all the elements in the stack.
{
	while(Is_Empty(st)==false)
		pop(st);
}

bool check_right(int c, int n_cols) // returns false if there is no column right to the given column, (i.e) the given column is the last column in the matrix.
{
	int x=n_cols-c;
	if(x>=2)
    return true;
	return false;
}

bool check_left(int c) //returns false if there is no column left to the given column, (i.e) the given column is the first column in the matrix.
{
	if(c==0)
	return false;
	return true;
}

bool check_down(int r, int n_rows) //returns false if there is no row under the given row, (i.e) the given row is the last row in the matrix.
{
	int x=n_rows-r;
	if(x>=2)
	return true;
	return false;
}

bool check_up(int r) // returns false if there is no row above the given row, (i.e) the given row is the first row in the matrix.
{
	if(r==0)
	return false;
	return true;
}

bool check_repetition(stack* st,int r,int c) // checks if the given position (row index & column index) has been already added to the given stack.
{
	if(st->count==0)
		return false;
	Node*temp=st->top;
	if(temp->r==r && temp->c==c)
		return true;
	for(int i=0; i<(st->count)-1; i++)
	{
		temp=temp->next;
		if(temp->r==r && temp->c==c)
			return true;
	}
return false;
}

bool back_tracking(stack*st) // checks if any element in the given stack is a back-tracking element.
{
	if(st->count<2)
	return false;
	Node*temp=st->top->next;
	   if((temp->n)>1)
	    return true;
	for(int i=0; i<(st->count)-2; i++)
	{
		temp=temp->next;
		if((temp->n)>1)
			return true;
	}
	return false;
}

string special_cases(int** mat,int n_rows,int n_cols,int r,int c) // checks if the given entrance is invalid (its value =1) or the given entrance is also the exit of the maze.
{	
	if(mat[r][c]==1)
	return "Invalid";
	if (check_right(c,n_cols)==false || check_left(c)==false || check_up(r)==false || check_down(r,n_rows)==false)
	return "The enterance is the exit";
	return "Niether";
}

string my_fn(int** mat,int n_rows,int n_cols,int r,int c,stack* st1,stack* st2) // this is the core function, returns "Trapped" if the there is no exit for the given entrance, "Done" otherwise.
{

	int n=0;
	if (check_right(c,n_cols)==false || check_left(c)==false || check_up(r)==false || check_down(r,n_rows)==false)
	{
		destroy_stack(st2);
		push(st1,r,c,n);
		return "Done";
	}
	if(mat[r][c-1]==0 && check_repetition(st2,r,c-1)==false)
		n++;
	if(mat[r][c+1]==0 && check_repetition(st2,r,c+1)==false)
		n++;
	if(mat[r+1][c]==0 && check_repetition(st2,r+1,c)==false)
		n++;
	if(mat[r-1][c]==0 && check_repetition(st2,r-1,c)==false)
		n++;
	if(check_repetition(st2,r,c)==false)
	{
		push(st1,r,c,n);
	    push(st2,r,c,n);
	}
	if(n==0 && st1->count==1)
	{
		destroy_stack(st2);
		return "Trapped";
	}
	
	else if(n>=1)
	{
	if ( mat[r][c-1]==0 && check_repetition(st2,r,c-1)==false)
    return my_fn(mat,n_rows,n_cols,r,c-1,st1,st2);
	else if ( mat[r][c+1]==0 && check_repetition(st2,r,c+1)==false)
	return my_fn(mat,n_rows,n_cols,r,c+1,st1,st2);
	else if ( mat[r+1][c]==0 && check_repetition(st2,r+1,c)==false)
    return my_fn(mat,n_rows,n_cols,r+1,c,st1,st2);
	else if ( mat[r-1][c]==0 && check_repetition(st2,r-1,c)==false)
	return my_fn(mat,n_rows,n_cols,r-1,c,st1,st2);
	}
	
		if(back_tracking(st1)==false)
		{
			destroy_stack(st2);
			return "Trapped";
		}
			pop(st1);
		return my_fn(mat,n_rows,n_cols,st1->top->r,st1->top->c,st1,st2);
	
}


void main()
{
	ifstream in("Maze.txt", ios::in);
	ofstream out("MazeSolution.txt", ios::out);
	string x,y,w;
	int n,m,z;
	char cm;
	stack st1,st2;
	st1.top=NULL;
	st1.count=0;
	st2.top=NULL;
	st2.count=0;
	while(!in.eof())
	{
	in>>x>>n>>cm>>m;
	int**mat=new int*[n];                                            
	for (int j=0;j<n; j++)
	mat[j]= new int[m];
   for (int k=0;k<n;k++)
   {
	  for (int l=0;l<m;l++)
	  {
		  in>>mat[k][l];
		  if(l!=m-1)
		     in>>cm;
      }
   
   }
	  in>>z;
      cor* arr= new cor[z];
	  for(int a=0;a<z;a++)
		  in>>arr[a].r>>cm>>arr[a].c;
      out<<x<<endl;
	  for(int b=0;b<z;b++)
	  {
		  out<<"Entrance: "<<arr[b].r<<","<<arr[b].c<<"    ";
		  y=special_cases(mat,n,m,arr[b].r,arr[b].c);
		  if(y=="Invalid")
			  out<<"Invalid"<<endl;
		  else if(y=="The enterance is the exit") 
			  out<<"The enterance is the exit"<<endl;
		  else if(y=="Niether")
		  {
			  w=my_fn(mat,n,m,arr[b].r,arr[b].c,&st1,&st2);
		      if(w=="Trapped")
				  out<<"Trapped"<<endl;
			  else
			  { 
				  while(Is_Empty(&st1)==false)
				  {
					  push(&st2,st1.top->r,st1.top->c,st1.top->n);
					  pop(&st1);
				  }
			  
				  while(Is_Empty(&st2)==false)
				  {
					  out<<"("<<st2.top->r<<","<<st2.top->c<<")";
						  if(st2.count!=1)
				          out<<"-";
						  pop(&st2);
				  }
			   out<<endl;
			  }
	     destroy_stack(&st1);
		 destroy_stack(&st2);
	    }

	  }

	}
in.close();
out.close();
}
