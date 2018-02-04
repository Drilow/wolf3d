#ifndef W3D_PARSE_H
# define W3D_PARSE_H

typedef struct			s_w3dparse
{
	int					fd;
	char				*buf;
	int					beenread;
	int					linesread;
	int					done;
}						t_w3dparse;

#endif
