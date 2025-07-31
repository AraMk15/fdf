NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCSDIR = ./src/
SRCSLIST = main.c \
			lines.c \
			math_helpers.c \
			generate_map.c \
			file_handling.c \
			file_handling2.c \
			draw.c \
			color_handling.c \
			hooks.c \
			transform.c \
			get_next_line.c \
			get_next_line_utils.c
SRCS = $(addprefix $(SRCSDIR), $(SRCSLIST))

OBJSDIR = ./obj/
OBJSLIST = $(SRCS:.c=.o)
OBJS = $(patsubst $(SRCSDIR)%.c, $(OBJSDIR)%.o, $(SRCS))

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_ARCHIVE_URL = https://cdn.intra.42.fr/document/document/34699/minilibx-linux.tgz
MINILIBX_ARCHIVE = minilibx-linux.tgz
MINILIBX_DIR = ./minilibx-linux
MINILIBX_PATH = $(MINILIBX_DIR)

TEST_MAPS_ARCHIVE_URL = https://cdn.intra.42.fr/document/document/34696/maps.zip
TEST_MAPS_ARCHIVE = maps.zip
TEST_MAPS_DIR_MAC = __MACOSX
TEST_MAPS_DIR = test_maps
TEST_MAPS_PATH = $(TEST_MAPS_DIR)

INCLUDE_PATHS = -I. -I$(MINILIBX_PATH) -I$(LIBFT_DIR)
MLX_LIBS = -L$(MINILIBX_PATH) -lmlx -lXext -lX11
MATH_LIB = -lm

RM = rm -f

all: $(NAME) $(TEST_MAPS_PATH)

$(NAME): $(MINILIBX_PATH)/libmlx.a $(OBJSDIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIBS) $(MATH_LIB) -o $(NAME)

$(MINILIBX_PATH)/libmlx.a:
	@echo "Checking for MiniLibX..."
	@if [ ! -d "$(MINILIBX_PATH)" ]; then \
		echo "MiniLibX not found. Downloading and installing..."; \
		curl -sSL $(MINILIBX_ARCHIVE_URL) -o $(MINILIBX_ARCHIVE) && \
		tar -xzf $(MINILIBX_ARCHIVE) && \
		$(RM) $(MINILIBX_ARCHIVE); \
	fi
	@make -C $(MINILIBX_PATH)

$(TEST_MAPS_PATH):
	@echo "Checking for test maps directory..."
	@if [ ! -d "$(TEST_MAPS_PATH)" ]; then \
		echo "Test maps directory not found. Downloading and extracting..."; \
		curl -sSL $(TEST_MAPS_ARCHIVE_URL) -o $(TEST_MAPS_ARCHIVE) && \
		unzip -q $(TEST_MAPS_ARCHIVE) && \
		$(RM) $(TEST_MAPS_ARCHIVE); \
		$(RM) -r $(TEST_MAPS_DIR_MAC); \
	fi

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJSDIR)
	make -C $(LIBFT_DIR) clean
	@if [ -d "$(MINILIBX_PATH)" ]; then \
		echo "Cleaning MiniLibX..."; \
		make -C $(MINILIBX_PATH) clean 2>/dev/null || true; \
	fi
	@if [ -d "$(TEST_MAPS_PATH)" ]; then \
		echo "Cleaning test maps..."; \
		$(RM) -r $(TEST_MAPS_PATH); \
	fi

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "Removing MiniLibX directory and archive..."
	$(RM) -r $(MINILIBX_PATH)
	$(RM) $(MINILIBX_ARCHIVE)
	@echo "Removing test maps directory and archive..."
	$(RM) -r $(TEST_MAPS_PATH)
	$(RM) $(TEST_MAPS_ARCHIVE)

re: fclean all

.PHONY: all clean fclean re
