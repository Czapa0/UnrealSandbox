#pragma once
#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f, 0, 1.f); 
#define DRAW_LINE(Start, End) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_LINE_SingleFrame(Start, End) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 10.f, FColor::Red, true, -1.f);
#define DRAW_POINT_SingleFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 10.f, FColor::Red, false, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocation, 100.f, FColor::Red, true, -1.f);
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if(GetWorld()) DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocation, 100.f, FColor::Red, false, -1.f);