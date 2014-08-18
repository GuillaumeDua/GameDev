#include "./AnimationLoader.h"

int	main(void)
{
  Animation	a("./char.anim");

  for (size_t it = 0; it < 255; ++it)
    {
      if (it % 10 == 0) std::cout << std::endl;
      std::cout << "[" << ((a.GetContent()[it] < 33 || a.GetContent()[it] > 126) ?
			   static_cast<int>((a.GetContent()[it])) : a.GetContent()[it]) << "]";
    }
  return 0;
}
