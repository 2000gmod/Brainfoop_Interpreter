TARGET = bfpint


FILE = examples/echo.bf
VERBOSE = -v
TIME = 100



CC = g++
CFLAGS = -Wall -g -lm -MMD


OBJDIR = obj
SRCDIR = src

OUTDIR = out

SOURCES := $(shell find . -name '*.cpp')
OBJECTS := $(subst .cpp,.o, $(subst ./src,./$(OBJDIR),$(SOURCES)))
DEPS := $(shell find . -name '*.d')

.PHONY: default
default:
	$(MAKE) $(TARGET)
# 	$(MAKE) run



$(TARGET): $(OBJECTS) #| $(OUTDIR)
	$(CC) -o $(TARGET) $^ $(CFLAGS) 


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)


include $(DEPS)

$(OUTDIR):
	mkdir -p $@

$(OBJDIR):
	mkdir -p $@
	$(shell rsync -a --include='*/' --exclude='*' $(SRCDIR)/ $(OBJDIR)/)


.PHONY: clean deepclean run

runVerbose: $(TARGET)
	./$(TARGET) $(FILE) $(VERBOSE) $(TIME)

run: $(TARGET)
	./$(TARGET) $(FILE)

clean:
	rm -f $(TARGET)
	rm -rf $(OUTDIR)

deepclean: clean
	rm -rf $(OBJDIR)