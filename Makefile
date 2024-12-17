CC := clang++
objects = ray.o
testfile := test.o
CXXFLAGS := -stdlib=libc++ -std=c++17
all: $(objects)
	$(CC) $^ -o ray

# Syntax - targets ...: target-pattern: prereq-patterns ...
# In the case of the first target, foo.o, the target-pattern matches foo.o and sets the "stem" to be "foo".
# It then replaces the '%' in prereq-patterns with that stem
$(objects): %.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@

test: $(testfile)
	$(CC) $^ -o test 

$(testfile): %.o: %.cpp
	$(CC) $(CXXFLAGS) -c $^ -o $@


# Note: all.c does not use this rule because Make prioritizes more specific matches when there is more than one match.
clean:
	rm -f *.o ray
