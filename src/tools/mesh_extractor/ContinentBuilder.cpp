#include "ContinentBuilder.h"
#include "TileBuilder.h"
#include "WDT.h"
#include "Utils.h"
#include "DetourNavMesh.h"

void ContinentBuilder::Build()
{
    char buff[50];
    sprintf(buff, "%03u.mmap", MapId);
    FILE* mmap = fopen(buff, "wb");
    dtNavMeshParams params;
    params.maxPolys = 32768;
    params.maxTiles = 4096;
    params.orig[0] = -17066.666f;
    params.orig[1] = 0.0f;
    params.orig[2] = -17066.666f;
    params.tileHeight = 533.33333f;
    params.tileWidth = 533.33333f;
    fwrite(&params, sizeof(dtNavMeshParams), 1, mmap);
    fclose(mmap);
    for (std::vector<TilePos>::iterator itr = TileMap->TileTable.begin(); itr != TileMap->TileTable.end(); ++itr)
    {
        TileBuilder builder(Continent, itr->X, itr->Y, TileMap, MapId);
        char buff[100];
        sprintf(buff, "%03u%02u%02u.mmtile", MapId, itr->X, itr->Y);
        FILE* f = fopen(buff, "r");
        if (f) // Check if file already exists.
        {
            fclose(f);
            continue;
        }
        uint8* nav = builder.Build();
        if (nav)
        {
            fclose(f);
            f = fopen(buff, "wb");
            MmapTileHeader header;
            header.size = builder.DataSize;
            fwrite(&header, sizeof(MmapTileHeader), 1, f);
            fwrite(nav, sizeof(unsigned char), builder.DataSize, f);
            fclose(f);
        }
        dtFree(nav);
        printf("[%02u,%02u] Tile Built!\n", itr->X, itr->Y);
    }
}