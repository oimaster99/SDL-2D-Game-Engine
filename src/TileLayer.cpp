#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TilesetList tilesets):m_TileSize (tilesize), m_ColCount(colcount), m_RowCount(rowcount), m_TileMap(tilemap), m_Tileset(tilesets)
{	

	for (unsigned int i = 0; i < m_Tileset.size(); i++)
	{
		TextureManager::GetInstance()->Load(m_Tileset[i].Name, "assets/maps/" + m_Tileset[i].Source);

	}
}

void TileLayer::Render()
{
	for (unsigned int i = 0; i < m_RowCount; i++)
	{
		for (unsigned int j = 0; j < m_ColCount; j++)
		{
			int TileID = m_TileMap[i][j];

			if (TileID == 0)
				continue;
			else
			{
				int index = 0;
				if (m_Tileset.size() > 1)
				{
					for (unsigned int k = 1; k < m_Tileset.size(); k++)
					{
						if (TileID > m_Tileset[k].FirstID && TileID < m_Tileset[k].LastID)
						{
							TileID = TileID + m_Tileset[k].TileCount - m_Tileset[k].LastID;
							index = k;
							break;
						}
					}
				}
			

				Tileset ts = m_Tileset[index];
				int tileRow = TileID/ts.ColCount;
				int tileCol = TileID - tileRow*ts.ColCount - 1;

				//If tile is on last column
				if(TileID % ts.ColCount == 0)
				{
					tileRow--;
					tileCol = ts.ColCount - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j*ts.TileSize, i*ts.TileSize, tileRow, tileCol);

			}

		}
	}
}

void TileLayer::Update()
{

}