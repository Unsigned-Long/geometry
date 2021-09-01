# <kbd>___Point___</kbd> cpp classes

## ***Author***

<kbd>___name___</kbd> csl  

<kbd>___email___</kbd> 3079625093@qq.com

## ***Overview***

___
The CPP library provides two dimension point template classes: <kbd>__Point2<_Ty>___</kbd> and <kbd>__Point3<_Ty>___</kbd>.It also provides related operations based on two kinds of points, such as conventional "write" operation, "read" operation and distance calculation of point set, and azimuth calculation based on point2. You can easily use it to assist development. Here are some details of this class.
___
## ***Using example***

### <kbd>__Point2<_Ty>___</kbd>  

```cpp
void foo_point2()
{
    Point2f p1(0.6, 0.4);
    Point2f p2(1.9, 2.7);
    Point2f p3(0.6, 0.4);
    Point2f p4(1.9, 2.7);
    std::list<Point2f> ls = {p1, p2, p3, p4};
    try
    {
        // distance between tow points
        std::cout << ns_test::distance(p1, p2) << std::endl;
        // the azimuth from p3 to p4
        std::cout << ns_test::azimuth(p3, p4) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        ns_test::writePoints(ls, "../output/point2.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        ns_test::readPoints(ls, "../output/point2.bin");
        // way two.
        // write mode : std::ios::out
        ns_test::writePoints(ls, "../output/point2.txt", std::ios::ou
        ls.clear();
        // read mode : std::ios::in
        ns_test::readPoints(ls, "../output/point2.txt", std::ios::in)
        // print points
        for (const auto &elem : ls)
        {
            std::cout << elem << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return;
}
```
### <kbd>__Point3<_Ty>___</kbd>  

```cpp
void foo_point3()
{
    Point3f p1(0.6, 0.4, 1.1);
    Point3f p2(1.9, 2.7, 2.3);
    Point3f p3(0.6, 0.4, 3.5);
    Point3f p4(1.9, 2.7, 4.6);
    std::list<Point3f> ls = {p1, p2, p3, p4};
    try
    {
        // distance between tow points
        std::cout << ns_test::distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        ns_test::writePoints(ls, "../output/point3.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        ns_test::readPoints(ls, "../output/point3.bin");
        // way two.
        // write mode : std::ios::out
        ns_test::writePoints(ls, "../output/point3.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        ns_test::readPoints(ls, "../output/point3.txt", std::ios::in);
        // print points
        for (const auto &elem : ls)
        {
            std::cout << elem << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return;
}
```

## ***Details***

### class <kbd>__Point2<_Ty>___</kbd>

[___typedefs___]()
```cpp
template <typename _Ty>
class Point2;

using Point2f = Point2<float>;
using Point2d = Point2<double>;
using Point2i = Point2<int>;
```
[___APIs___]()

```cpp
// calculate the distance between two points
template <typename _Ty>
float distance(const Point2<_Ty> &p1, const Point2<_Ty> &p2)

// calculate the azimuth
template <typename _Ty>
float azimuth(const Point2<_Ty> &from, const Point2<_Ty> &to)

// write points' data to file
template <typename _Ty>
void writePoints(const std::list<Point2<_Ty>> &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary)

// read points'data from the file
template <typename _Ty>
void readPoints(std::list<Point2<_Ty>> &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)

// put point to ostream
template <typename _Ty>
std::ostream &operator<<(std::ostream &os, const Point2<_Ty> &p)
```

### class <kbd>__Point3<_Ty>___</kbd>

[___typedefs___]()
```cpp
template <typename _Ty>
class Point3;

using Point3f = Point3<float>;
using Point3d = Point3<double>;
using Point3i = Point3<int>;
```
[___APIs___]()

```cpp
// calculate the distance between two points
template <typename _Ty>
float distance(const Point3<_Ty> &p1, const Point3<_Ty> &p2)

// write points' data to file
template <typename _Ty>
void writePoints(const std::list<Point3<_Ty>> &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::out | std::ios::binary)
template <typename _Ty>

// read points'data from the file
void readPoints(std::list<Point3<_Ty>> &points, const std::string &filePath, std::ios_base::openmode mode = std::ios::in | std::ios::binary)

// put point to ostream
template <typename _Ty>
std::ostream &operator<<(std::ostream &os, const Point3<_Ty> &p)
```

## ***Others***

```cpp
// the const value of PI
constexpr double PI = 3.1415926535;

// write binary data to file
template <typename _Ty>
void writeBinaryData(const std::list<_Ty> &ls, std::ofstream &file)

// read binary data from file
template <typename _Ty>
void readBinaryData(std::list<_Ty> &ls, std::ifstream &file)
```

For other implementation details, please refer to the source code.