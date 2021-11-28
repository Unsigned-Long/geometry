# <kbd>___Point___</kbd> cpp classes

## ***Author***

<kbd>___name___</kbd> csl  

<kbd>___email___</kbd> 3079625093@qq.com

## ***Overview***

___
The CPP library provides two dimension point template classes: <kbd>__Point2<_Ty>___</kbd> and <kbd>__Point3<_Ty>___</kbd>.It also provides related operations based on two kinds of points, such as conventional "write" operation, "read" operation and distance calculation of point set, and azimuth calculation based on point2. You can easily use it to assist development. Here are some details of this class.  
And because it's a templat class, you can just copy the head file to your project and use it.
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
        std::cout << distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        writePoints2(ls, "../output/point2.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        readPoints2(ls, "../output/point2.bin");
        // way two.
        // write mode : std::ios::out
        writePoints2(ls, "../output/point2.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        readPoints2(ls, "../output/point2.txt", std::ios::in);
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
        std::cout << distance(p1, p2) << std::endl;
        // write and read point data
        // way one.
        // default write mode : std::ios::out | std::ios::binary
        writePoints3(ls, "../output/point3.bin");
        ls.clear();
        // default read mode : std::ios::in | std::ios::binary
        readPoints3(ls, "../output/point3.bin");

        // way two.
        // write mode : std::ios::out
        writePoints3(ls, "../output/point3.txt", std::ios::out);
        ls.clear();
        // read mode : std::ios::in
        readPoints3(ls, "../output/point3.txt", std::ios::in);
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

### <kbd> ___PointSet<PointType,Alloc>___</kbd> 
```cpp
void foo_pointset()
{
    PointSet2f set;
    set.push_back(Point2f(1, 2));
    set.push_back(Point2f(2, 3));
    writePoints2(set, "../output/pointset.csv", std::ios::out);
    set.clear();
    readPoints2(set, "../output/pointset.csv", std::ios::in);
        for (const auto &point : set)
        std::cout << point << std::endl;
    return;
}
```

### <kbd>__Point_cast<_Ty>___</kbd>  
```cpp
void foo_ponitCast_test()
{
    Point3f p(1, 2, 6);
    Point2f p2(2, 6);
    auto ary = static_cast<Point3f::ary_type>(p);
    auto ary2 = static_cast<Point2f::ary_type>(p2);

    std::cout << ary[0] << ',' << ary[1] << ',' << ary[2] << std::endl;
    std::cout << ary2[0] << ',' << ary2[1] << std::endl;

    std::cout << Point3f(ary) << std::endl;
    std::cout << Point2f(ary2) << std::endl;

    return;
}
```

### <kbd>__Triangle2<_Ty>___</kbd>  

```cpp
void foo_triangle2()
{
    ns_geo::Point2<double> points[3] = {
        Point2d(0, 0),
        Point2d(2, 2),
        Point2d(2, 0)};
    ns_geo::Triangle2d tri(points);
    std::cout << tri << std::endl;
    std::cout << "area : " << tri.area() << std::endl;
    std::cout << "perimeter : " << tri.perimeter() << std::endl;
    return;
}
```

### <kbd>__Triangle3<_Ty>___</kbd>  

```cpp
void foo_triangle3()
{
    ns_geo::Point3<double> points[3] = {
        Point3d(0, 0, 0),
        Point3d(2, 2, 2),
        Point3d(2, 0, 0)};
    ns_geo::Triangle3d tri(points);
    std::cout << tri << std::endl;
    std::cout << "area : " << tri.area() << std::endl;
    std::cout << "perimeter : " << tri.perimeter() << std::endl;
    return;
}
```

### <kbd>__Line2<_Ty>___</kbd>  

```cpp
void foo_line2()
{
    ns_geo::Line2d line(Point2d(0, 0), Point2d(2, 2));
    std::cout << line << std::endl;
    std::cout << "length : " << line.length() << std::endl;
    return;
}
```

### <kbd>__Line3<_Ty>___</kbd>  

```cpp
void foo_line3()
{
    ns_geo::Line3d line(Point3d(0, 0, 0), Point3d(2, 2, 2));
    std::cout << line << std::endl;
    std::cout << "length : " << line.length() << std::endl;
    return;
}
```

### <kbd>__Rectangle2<_Ty>___</kbd>  

```cpp
void foo_rectangle2()
{
    ns_geo::Rectangle2d rect(0, 4, 1, 0);
    std::cout << rect << std::endl;
    std::cout << "area : " << rect.area() << std::endl;
    return;
}
```

For other implementation details, please refer to the source code.