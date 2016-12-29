
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#if (defined __USE_BSD || defined __USE_UNIX98) \
    && defined __S_IFSOCK
# define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)
#endif

int main()
{      int total=0;
      char p[20],r[100];
      DIR *dir;
      struct stat sb;
      struct dirent *direntp;
       struct passwd *pw;
       struct group  *gr;
      char *pwd;
  
    pwd=getenv("PWD");
               
    dir=opendir(pwd);
     if(dir==NULL)
     { perror("failed");
       exit(0);
     }
   if (stat(pwd, &sb) == -1) {
        perror("stat");
        exit(1);
    }
    

		while ( ( direntp = readdir( dir ) ) != NULL ) {
			strcpy(p,direntp->d_name);
              
                         
                   
                   if(p[0]=='.'|| p[1]=='.')
                   continue;
                  else	
                   {      strcpy(r,pwd);	 	              
                        
                        strcat(r,"/");
                        strcat(r,p);
                     
                  if (stat(r,&sb) == -1)
                  {  printf("%s",direntp->d_name);
                     printf("%s",p);
                     perror("stat");
                    continue;
                  }

    if(S_ISDIR(sb.st_mode))
    printf("d");
    if(S_ISREG(sb.st_mode))
    printf("-");
    if(S_ISCHR(sb.st_mode))
    printf("c");
    if(S_ISBLK(sb.st_mode))
    printf("b");
    if(S_ISFIFO(sb.st_mode))
    printf("p");
    if(S_ISLNK(sb.st_mode))
    printf("l");
    /*if(S_ISSOCK(sb.st_mode))
    printf("s");*/
     
            
        
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IRUSR)? "r":"-");
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IWUSR)? "w":"-");
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IXUSR)? "x":"-");
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IRGRP)? "r":"-");
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IWGRP)? "w":"-");
    printf(stat(r,&sb) == 0 && (sb.st_mode & S_IXGRP)? "x":"-");
    printf((sb.st_mode & S_IROTH)? "r":"-");
    printf((sb.st_mode & S_IWOTH)? "w":"-");
    printf((sb.st_mode & S_IXOTH)? "x":"-");
    printf(" %d ",(int)sb.st_nlink);
  



    
   
    pw=getpwuid(sb.st_uid);
    
    gr=getgrgid(sb.st_gid);  
    printf("%s",pw->pw_name);
    printf(" %s ",gr->gr_name);
    printf("%d ",(int)sb.st_size);
    printf("%.12s ", 4+ctime(&sb.st_mtime));
    printf("%s",direntp->d_name);
    printf("\n");
    total=total+sb.st_size;
    
  }
}

   
  
   exit(1);
   return 0;

}




 
