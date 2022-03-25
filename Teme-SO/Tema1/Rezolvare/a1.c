#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int string_equals(char*str1,char*str2)
{
	return strcmp(str1,str2)==0;
}

int string_equals_n(char*str1,char*str2,int n)
{
	return strncmp(str1,str2,n)==0;
}

int
list_function(char*path,char*name_ending,int name_ends_option,int perm_execute,int recursive,int recursive_first_call)
{
	DIR*d=opendir(path);
	if(d==0)
	{
		printf("ERROR\ninvalid directory path\n");
		return 0;
	}
	if(recursive_first_call==1)
	{
		printf("SUCCESS\n");
	}
	char file_path[1024];
	struct stat statbuf;
	struct dirent*entry;
	while(1)
	{
		entry=readdir(d);
		if(entry==0)
		{
			closedir(d);
			return 0;
		}
		if(string_equals(".",entry->d_name)||string_equals("..",entry->d_name))
		{
			continue;
		}
		if(name_ends_option==1)
		{
			if(string_equals(entry->d_name+strlen(entry->d_name)-strlen(name_ending),name_ending)==0)
			{
				continue;
			}
		}
		snprintf(file_path,1024,"%s/%s",path,entry->d_name);
		if(lstat(file_path,&statbuf)==0)
		{
			if(perm_execute==1&&(statbuf.st_mode&S_IXUSR)==0)
			{
				continue;
			}
			if(S_ISREG(statbuf.st_mode))
			{
				printf("%s\n",file_path);

			}
			else
			{
				if(S_ISDIR(statbuf.st_mode))
				{
					printf("%s\n",file_path);
					if(recursive==1)
					{
						list_function(file_path,name_ending,name_ends_option,perm_execute,recursive,0);
					}
				}
			}
		}
	}
}

int parse_function(char*path)
{
	int fd=open(path,O_RDONLY);
	if(fd==-1)
	{
		printf("ERROR\ninvalid file");
	}
	unsigned char magic;
	unsigned short header_size,version;
	unsigned char no_of_sections;
	read(fd,&magic,1);
	read(fd,&header_size,2);
	read(fd,&version,2);
	read(fd,&no_of_sections,1);
	if(magic!='y')
	{
		printf("ERROR\nwrong magic");
		close(fd);
		return 1;
	}
	if(version<16||version>60)
	{
		printf("ERROR\nwrong version");
		close(fd);
		return 1;
	}
	if(no_of_sections<2||no_of_sections>19)
	{
		printf("ERROR\nwrong sect_nr");
		close(fd);
		return 1;
	}
	unsigned int sect_type;
	for(int i=0;i<no_of_sections;i++)
	{
		lseek(fd,7,SEEK_CUR);
		read(fd,&sect_type,4);
		if(sect_type!=86&&sect_type!=62&&sect_type!=16)
		{
			printf("ERROR\nwrong sect_types");
			close(fd);
			return 1;
		}
		lseek(fd,8,SEEK_CUR);
	}
	lseek(fd,6,SEEK_SET);
	printf("SUCCESS\n");
	printf("version=%d\n",version);
	printf("nr_sections=%d\n",no_of_sections);
	for(int i=0;i<no_of_sections;i++)
	{
		char name[8];
		name[7]=0;
		unsigned int sect_size;
		read(fd,name,7);
		read(fd,&sect_type,4);
		lseek(fd,4,SEEK_CUR);
		read(fd,&sect_size,4);
		printf("section%d: %s %d %d\n",i+1,name,sect_type,sect_size);
	}
	close(fd);
	return 0;
}

int validate_section_file(char*path)
{
	int fd=open(path,O_RDONLY);
	if(fd==-1)
	{
		return 0;
	}
	unsigned char magic;
	unsigned short header_size,version;
	unsigned char no_of_sections;
	read(fd,&magic,1);
	read(fd,&header_size,2);
	read(fd,&version,2);
	read(fd,&no_of_sections,1);
	if(magic!='y')
	{
		close(fd);
		return 0;
	}
	if(version<16||version>60)
	{
		close(fd);
		return 0;
	}
	if(no_of_sections<2||no_of_sections>19)
	{
		close(fd);
		return 0;
	}
	unsigned int sect_type;
	for(int i=0;i<no_of_sections;i++)
	{
		lseek(fd,7,SEEK_CUR);
		read(fd,&sect_type,4);
		if(sect_type!=86&&sect_type!=62&&sect_type!=16)
		{
			close(fd);
			return 0;
		}
		lseek(fd,8,SEEK_CUR);
	}
	int sec_count=0;
	for(int i=0;i<no_of_sections;i++)
	{
		unsigned int offset,size;
		lseek(fd,6+i*(19)+11,SEEK_SET);
		read(fd,&offset,4);
		read(fd,&size,4);
		lseek(fd,offset,SEEK_SET);
		char c[size+1];
		c[size]=0;
		read(fd,&c,size);
		int line_count=1;
		for(int j=0;j<size;j++)
		{
			if(c[j]==0xa||c[j]==0xd)
			{
				if(j!=0&&j!=size-1)
				{
					if(c[j-1]!=0xa&&c[j-1]!=0xd)
					{
						line_count++;
					}
				}
			}
		}
		if(line_count==13)
		{
			sec_count++;
		}
		if(sec_count==3)
		{
			return 1;
		}
	}
	close(fd);
	return 0;
}

int findall_function(char*path,int recursive_first_call)
{
	DIR*d=opendir(path);
	if(d==0)
	{
		printf("ERROR\ninvalid directory path\n");
		return 0;
	}
	if(recursive_first_call==1)
	{
		printf("SUCCESS\n");
	}
	char file_path[1024];
	struct stat statbuf;
	struct dirent*entry;
	while(1)
	{
		entry=readdir(d);
		if(entry==0)
		{
			closedir(d);
			return 0;
		}
		if(string_equals(".",entry->d_name)||string_equals("..",entry->d_name))
		{
			continue;
		}
		snprintf(file_path,1024,"%s/%s",path,entry->d_name);
		if(lstat(file_path,&statbuf)==0)
		{
			if(S_ISREG(statbuf.st_mode))
			{
				if(validate_section_file(file_path)==1)
				{
					printf("%s\n",file_path);
				}

			}
			else
			{
				if(S_ISDIR(statbuf.st_mode))
				{
					findall_function(file_path,0);
				}
			}
		}
	}
}

int main(int argc,char**argv)
{
	if(argc==2)
	{
		if(string_equals(argv[1],"variant"))
		{
			printf("20111");
			return 0;
		}
	}
	int list=0,recursive=0,recursive_first_call=1,name_ends_option=0,perm_execute=0,parse=0,findall=0;
	char path[1024],name_ending[1024];
	if(argc>2)
	{
		for(int i=1;i<argc;i++)
		{
			if(string_equals(argv[i],"list"))
			{
				list=1;
			}
			else
			{
				if(string_equals(argv[i],"recursive"))
				{
					recursive=1;
				}
				else
				{
					if(string_equals_n(argv[i],"path=",5))
					{
						strcpy(path,argv[i]+5);
					}
					else
					{
						if(string_equals_n(argv[i],"name_ends_with=",15))
						{
							name_ends_option=1;
							strcpy(name_ending,argv[i]+15);
						}
						else
						{
							if(string_equals(argv[i],"has_perm_execute"))
							{
								perm_execute=1;
							}
							else
							{
								if(string_equals(argv[i],"parse"))
								{
									parse=1;
								}
								else
								{
									if(string_equals(argv[i],"findall"))
									{
										findall=1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(list==1)
	{
		list_function(path,name_ending,name_ends_option,perm_execute,recursive,recursive_first_call);
		return 0;
	}
	if(parse==1)
	{
		parse_function(path);
		return 0;
	}
	if(findall==1)
	{
		findall_function(path,recursive_first_call);
		return 0;
	}
	return 1;
}

