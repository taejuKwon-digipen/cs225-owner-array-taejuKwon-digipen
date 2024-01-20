# CS225 Implement owner_array

For this assignment you will be implementing a class to represent an **owning** dynamic array. You will also be writing unity tests utilizing the `catch2` framework to help verify your implementation.

# Implementing owner_array

```c++
template<typename T> class owner_array;
```

You are to create a heap-allocated array. The number of elements are determined at construction and fixed thereafter. The elements are mutable unless T is a const type. Basically a span that allocates and owns its elements.

`owner_array` is not re-sizable, and is a safe way to refer to a heap-allocated fixed-size array. Unlike vector, it is intended to replace array-`new[]`. It simply refers to a "dynamic" or heap-based array.

## Member types

Member type| Definition
-|-
element_type  |  `T`
value_type | `std::remove_cv_t<T>`
size_type  | `int`
difference_type |`std::ptrdiff_t`
pointer | `T*`
const_pointer  | `const T*`
reference  | `T&`
const_reference |`const T&`
iterator  |  implementation-defined of a [Contiguous Iterator](https://en.cppreference.com/w/cpp/named_req/ContiguousIterator) _(note that a regular T* would satisfy this)_
reverse_iterator  |  `std::reverse_iterator<iterator>`

## Member functions

### Constructor

Declaration|Explanation
-|-
`owner_array();`| Constructs an empty array with `data() == nullptr` and `size() == 0`
`explicit owner_array( size_type count, const T& value = T());`|  Constructs the container with `count` copies of elements with value `value`.
`template< class InputIt >owner_array( InputIt first, InputIt last);`| Constructs the container with the contents of the range [first, last)
`owner_array( const owner_array& other );` | Copy constructor. Constructs the container with the copy of the contents of `other`
`owner_array( owner_array&& other ) noexcept;`|Move constructor. Constructs the container with the contents of `other` using move semantics. After the move, `other` is guaranteed to be `empty()`.
`owner_array( std::initializer_list<T> init);` | Constructs the container with the contents of the initializer list `init`.


#### Parameters
name|description
-|-
count   |   the size of the container, values less than 0 will trigger a [`std::invalid_argument`](https://en.cppreference.com/w/cpp/error/invalid_argument)
value   |   the value to initialize elements of the container with
first, last |   the range to copy the elements from
other   |   another container to be used as source to initialize the elements of the container with
init    |   initializer list to initialize the elements of the container with

### Destructor

`~owner_array` - Destructs the `owner_array`. The destructors of the elements are called and the used storage is released. Note, that if the elements are pointers, the pointed-to objects are not destroyed.

### operator=

Declaration|Explanation
-|-
`owner_array& operator=( const owner_array& other );`| Copy assignment operator. Replaces the contents with a copy of the contents of other.
`owner_array& operator=( owner_array&& other );`| Move assignment operator. Replaces the contents with those of `other` using move semantics (i.e. the data in other is moved from other into this container). After the move, `other` is guaranteed to be `empty()`.

### Iterators

Declaration|Explanation
-|-
`iterator begin() const noexcept;` | Returns an iterator to the first element of the `owner_array`. If the `owner_array` is empty, the returned iterator will be equal to `end()`.
`iterator end() const noexcept;` | Returns an iterator to the element following the last element of the `owner_array`. This element acts as a placeholder; attempting to access it results in undefined behavior.
`reverse_iterator rbegin() const noexcept;` | Returns a reverse iterator to the first element of the reversed `owner_array`. It corresponds to the last element of the non-reversed `owner_array`. If the `owner_array` is empty, the returned iterator is equal to `rend()`.
`reverse_iterator rend() const noexcept;`| Returns a reverse iterator to the element following the last element of the reversed `owner_array`. It corresponds to the element preceding the first element of the non-reversed `owner_array`. This element acts as a placeholder, attempting to access it results in undefined behavior.

### Element Access

Declaration|Explanation
-|-
`reference front() const;`| Returns a reference to the first element in the `owner_array`. Calling front on an empty `owner_array` results in undefined behavior.
`reference back() const;`| Returns a reference to the last element in the `owner_array`. Calling back on an empty `owner_array` results in undefined behavior.
`reference operator[](size_type idx) const;`| Returns a reference to the `idx`-th element of the sequence. Indices may also be negative numbers, to start counting from the right. Note that since -0 is the same as 0, negative indices start from -1. The behavior is undefined if `idx` is out of range (i.e., if it is less than `-size()` or greater than or equal to `size()`).
`pointer data() const noexcept;`|Returns a pointer to the beginning of the sequence.

### Observers

Declaration|Explanation
-|-
`size_type size() const noexcept;`|size_type size() const noexcept;
`size_type size_bytes() const noexcept;`|Returns the size of the sequence in bytes.
`[[nodiscard]] bool empty() const noexcept;`| Checks if the `owner_array` is empty. `true` if the `owner_array` is empty (i.e., `size()` == 0); `false` otherwise.

## Non-Member functions

```c++
template<typename T>
gsl::span<const unsigned char, gsl::dynamic_extent> as_bytes(const owner_array<T>& array) noexcept;
```
Obtains a view to the object representation of the elements of the owner_array `array`. The extent of the returned span is `gsl::dynamic_extent`.

Returns a span constructed with `{reinterpret_cast<const unsigned char*>(array.data()), array.size_bytes()}`.


```c++
template<typename T>
gsl::span<unsigned char, gsl::dynamic_extent> as_writable_bytes(owner_array<T>& array) noexcept;
```

Obtains a **writable** view to the object representation of the elements of the owner_array `array`. The extent of the returned span is `gsl::dynamic_extent`.

Returns a span constructed with `{reinterpret_cast<unsigned char*>(array.data()), array.size_bytes()}`.

# Unit Tests

Unit tests will be written using the [Catch2](https://github.com/catchorg/Catch2) framework. Unfamiliar with Catch2? Then checkout their [tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top).

In particular you need to use [**Type parametrized test cases**](https://github.com/catchorg/Catch2/blob/master/docs/test-cases-and-sections.md#type-parametrised-test-cases).

The unit tests will be a collaborative effort from the whole class. Instead of each student writing a unit test for every part of the `owner_array` we will distribute the work. Each student implementation will have to pass the class created unit tests. Each student must implement at least 4 different tests.

Look for a Google Spreadsheet link on the course site. You must put your name under three different categories and you can only put your name under a category if the previous column is filled.

For example

Test Case	| Section 1 Author | Section 2 Author | Section 3 Author
-|-|-|-
Test 1      | Fun Frank | | 
Test 2      | | | 
Test 3      | Silly Sally | | 

I can only put my name in the Test2 row.

The goal is to have an even distribution of authors and tests :

Test Case	| Section 1 Author | Section 2 Author | Section 3 Author
-|-|-|-
Test 1      | Fun Frank     | Rudy Castan   | Silly Sally   
Test 2      | Rudy Castan   | Silly Sally   | Fun Frank     
Test 3      | Silly Sally   | Fun Frank     | Rudy Castan   


In this example, all the tests will have 4 different versions. So for the Test1 **TEMPLATE_TEST_CASE**, Frank, Rudy and Sally will each come up with their own test **SECTION**. The test SECTION must contain the author's DigiPen username.

For example, tests should look something like this:
```c++
TEMPLATE_TEST_CASE( "testing vector resize", "[vector][template]", int, std::string, (std::tuple<int,float>) ) {

    std::vector<TestType> v( 5 );

    REQUIRE( v.size() == 5 );
    REQUIRE( v.capacity() >= 5 );

    SECTION( "resizing bigger changes size and capacity - fun.frank" ) {
        v.resize( 10 );

        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
    SECTION( "resizing smaller changes size but not capacity - rudy.castan" ) {
        v.resize( 0 );

        REQUIRE( v.size() == 0 );
        REQUIRE( v.capacity() >= 5 );

        SECTION( "We can use the 'swap trick' to reset the capacity" ) {
            std::vector<TestType> empty;
            empty.swap( v );

            REQUIRE( v.capacity() == 0 );
        }
    }
    SECTION( "reserving smaller does not change size or capacity - silly.sally ) {
        v.reserve( 0 );

        REQUIRE( v.size() == 5 );
        REQUIRE( v.capacity() >= 5 );
    }
}
```

There will also be a shared repo for the unit tests. It will be added to your assignment as a [*git submodule*](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

# Requirements

Your implementation of the `owner_array` must be written using your own low level code. That means you cannot use standard containers nor you can you use smart pointers. You must use `new[]` and `delete[]`.

However you should utilize the [Guideline Support Library](https://github.com/microsoft/GSL) where you can and follow the C++ core guidelines.

You may and should use `std::reverse_iterator` to provide reverse iterators.

# Grading Rubric

- [x] [**core**] Implemented all of the `owner_array` class
- [x] [**core**] Implementation is written with your own low level code
- [ ] [**core**] Contributed 4 or more meaningful test cases
- [x] [**core**] Your personal repo has the latest version of the unit test repo as a submodule
- [x] Running `git shortlog -sn --no-merges` shows that all members of the class contributed to the unit test repository in the same order of magnitude
- [x] Utilizes the [Guideline Support Library](https://github.com/microsoft/GSL)
- [x] Utilize Member type definitions as much as possible
- [x] Project is configured to check against the C++ Core Guidelines and just the default Microsoft ones
- [x] Project is configured to automatically run static analysis
- [x] All source files compile without warnings and without errors.
- [x] Correct files submitted. No unnecessary files submitted.
- [x] **All** Source Code has a proper header comment: Name, Assignment Name, Course Number, Term & Year.
- [x] Followed the appropriate Code Quality Guidelines and Code Style Guidelines.
- [x] All requirements that are completed are checked off here by replacing the `[ ]` with `[x]`

Scores for Exercises will be given as the following:

Score        | Assessment
------------ | ----------
Zero         | Nothing turned in at all
Failing      | Close to meeting core requirements
Rudimentary  | Meets all of the core requirements
Satisfactory | Close to meeting all requirements
Good         | Clearly meets all requirements 
Excellent    | High quality, well beyond the requirements
