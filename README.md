# cpp-utils-collections

```bash
include(FetchContent)
fetchcontent_declare(cpp_utils
    GIT_REPOSITORY https://github.com/Dauxdu/cpp-utils-collections.git
    GIT_TAG main
)
fetchcontent_makeavailable(cpp_utils)
```

### InputNumeric example

```cpp
import std;
import nin;

int main()
{
    while (true)
    {
        try
        {
            std::print("Enter a number 0: ");
            auto value = nin::input_numeric<int>(0, 0);
            std::println("Parsed: {}", value); // 0
            break;
        }
        catch (const std::exception &e)
        {
            std::println("Error: {}", e.what());
            continue;
        }
    }

    return 0;
}
```
