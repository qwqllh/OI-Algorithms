void getnext() 
{ 
	next[1]=0; 
	for (i=2;i<=lenb;i++) 
	{ 
		int j=next[i-1]; 
		while (j&&b[j+1]!=b[i]) j=next[j]; 
		if (b[j+1]==b[i]) j++; 
		next[i]=j; 
	} 
} 
void getf() 
{ 
	for (i=1;i<=lena;i++) 
	{ 
		int j=f[i-1]; 
		while (j&&a[i]!=b[j+1]) j=next[j]; 
		if (a[i]==b[j+1]) j++; 
		f[i]=j; 
	} 
}