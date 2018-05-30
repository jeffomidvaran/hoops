#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

int is_readable(char *file_name)
{
	return access(file_name, R_OK) == 0;
}
int is_file(char *file_name)
{
	struct stat fileStat;
	if(stat(file_name, &fileStat) < 0)
		return 0;
	return !(S_ISDIR(fileStat.st_mode));
}
struct args
{
	char *pattern;
	int file_index;
	char *file_name;
};
//void search(char *pattern, int file_index, char *file_name)
void *search(void *info)
{
	struct args *arg = (struct args *) info;
	if(!is_readable(file_name))
		return;
	if(is_file(file_name))
	{
		add_all_matching_lines(info.pattern, info.file_index, info.file_name);
	}
	else // might be else if for is_directory
	{
		char *entries[10000];
		int dir_size = contents_of(info.file_name, entries);
		for(int i = 1; i < dir_size; ++i)
    	{
        	struct args arg;
        	strcpy(arg.pattern, info.pattern);
        	arg.file_index = i;
        	strcpy(arg.file_name, strcat(info.file_name, entries[i-1])); 
        	search((void *) arg);
        }
	}
	pthread_exit((void *) 0);
}
int main(int argc, char *argv[])
{
	//maybe change
	if (argc != 3)
	{
		perror("Usage: search pattern file");
		exit(EXIT_FAILURE);
	}
	pthread_t threads[argc-2];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(int file_index = 1; file_index < argc-1; ++file_index)
	{
		struct args info;
		strcpy(info.pattern, argv[1]);
		info.file_index = file_index;
		strcpy(info.file_name, argv[file_index+1]);
		pthread_create(&threads[file_index-1], &attr, search, 
			(void *) info);
		//search(argv[1], file_index, argv[file_index+1]);
	}
	return 0;
}
