enum GameMode
{
  PVP,
  PVC
};

GameMode gamemode_of_int(int x)
{
  switch (x)
  {
  case 0:
    return PVP;
    break;
  case 1:
    return PVC;
    break;
  }
}