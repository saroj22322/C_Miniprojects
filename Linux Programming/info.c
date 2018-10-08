#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
	fprintf(stdout,"\n");
	if( argc < 2) {
		fprintf(stderr,"\t Syntax Failure : info [dataname] [dataname2] ... \n\n");
		return EXIT_FAILURE;
	}
	int count = 1, i = 0, id = -1;
	struct stat info;
	char *name;
	mode_t types[7] = {S_IFBLK, S_IFCHR, S_IFDIR, S_IFIFO, S_IFREG, S_IFLNK, S_IFSOCK};
	char *types_name[] = {"Block Special Device","Character Special Device", "Directory",
				"FIFO Special", "Regular", "Link", "Socket"};
	char perm[10];
	mode_t permission[9] = {S_IRUSR,S_IWUSR,S_IXUSR,S_IRGRP,S_IWGRP,S_IXGRP,S_IROTH,S_IWOTH,S_IXOTH};
	char bits[3] = {'r','w','x'};
	while(count++ < argc) {
		name = *(++argv);	
		if(stat(name,&info) != -1){
			fprintf(stdout,"\t\t Name : %s\n", name);
			fprintf(stdout,"\t\t Size : %ld bytes\n", info.st_size);
			//Printing the size of data.
			for( i = 0; i < 7; i++) {
				if(info.st_mode & types[i]){
					id = i;
					break;
				}			
			}
			if(id != -1)
			fprintf(stdout,"\t\t Data type : %s\n",types_name[id]);
			else
			fprintf(stdout,"\t\t Data type : Undefined\n");
			//Printing the data type if available.	
			for( i = 0; i < 9;) {
				int j;
				for( j = 0; j <= 2; j++) {
					if(info.st_mode & permission[i]) {
						perm[i] = bits[j];
					} else {
						perm[i] = '-';
					}
					i++;
				}			
			}
			perm[i] = '\0';	
			fprintf(stdout,"\t\t Permission : (%o / %s)\n", info.st_mode, perm);
			//Printing the file permission for user, group and other.	
			fprintf(stdout,"\t\t User ID : %u\t Group ID : %u\n", info.st_uid, info.st_gid);
			//Printing the User ID and Group ID of the file owner.
			fprintf(stdout,"\t\t Parent Device ID : %2d/%2d\n",major(info.st_dev),minor(info.st_dev));
			//Printing the device ID where the file is located.
			if(id == 0 || id == 1)
			fprintf(stdout,"\t\t Device ID : %2d/%2d\n",major(info.st_rdev),minor(info.st_rdev));
			//Printing the ID of the device if file is a device.
			fprintf(stdout,"\t\t Node number : %ld\n", info.st_ino);
			//Printing the file serial number.				
			fprintf(stdout,"\t\t Blocks : %ld\t Block size : %ld bytes\n", info.st_blocks, info.st_blksize);
			//Printing the number of blocks allocated for this object and size of each block.
			fprintf(stdout,"\t\t Number of links : %u\n", info.st_nlink);	
			//Printing the number of hard links to the file.
			fprintf(stdout,"\t\t Last Accessed : %s", ctime(&info.st_atime));
			fprintf(stdout,"\t\t Last Modified : %s", ctime(&info.st_mtime));
			fprintf(stdout,"\t\t Last Changed : %s", ctime(&info.st_ctime));
			//Printing out last accessed, last modified and last status changed time of the file.
			fprintf(stdout,"\n");

		} else {
			fprintf(stderr,"\tFailure : \"%s\" data doesnot exist.\n\n", name);		
		}		 
	}
	return EXIT_SUCCESS;
}
