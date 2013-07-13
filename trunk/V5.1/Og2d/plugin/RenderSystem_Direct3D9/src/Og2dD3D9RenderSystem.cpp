#include "Og2dD3D9Prerequisites.h"
#include "Og2dD3D9RenderSystem.h"
#include "Og2dD3D9Shape.h"
#include "Og2dD3D9Texture.h"

namespace Og2d
{
	// D3D渲染系统名
	static const String		D3D9_RENDER_SYSTEM_NAME = "Direct3D9 Render System";

	/**
	 *
	 * \return 
	 */
	D3D9RenderSystem::D3D9RenderSystem()
		: m_pd3dDevice(NULL), m_pD3D(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	D3D9RenderSystem::~D3D9RenderSystem()
	{
		if (m_pd3dDevice != NULL)
		{
			m_pd3dDevice->Release();
			m_pd3dDevice = NULL;
		}

		if (m_pD3D != NULL)
		{
			m_pD3D->Release();
			m_pD3D = NULL;
		}
	}

	/**
	 *
	 * \return 
	 */
	const String& D3D9RenderSystem::getTypeName() const
	{
		return D3D9_RENDER_SYSTEM_NAME;
	}

	/**
	 *
	 * \param hWnd 
	 * \param isFullScreen 
	 * \param bbSize 
	 * \param isVsvy 
	 * \return 
	 */
	bool	D3D9RenderSystem::createGriaphicsDevice(
													HWND hWnd,
													bool isFullScreen,
													const Size& bbSize,
													bool isVsvy 
													)
	{
		if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			return 0;
		}
		else
		{	
			D3DADAPTER_IDENTIFIER9 dai;
			if (!FAILED(m_pD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &dai)))
			{
				char tmp[512];

				int Product = HIWORD(dai.DriverVersion.HighPart);
				int Version = LOWORD(dai.DriverVersion.HighPart);
				int SubVersion = HIWORD(dai.DriverVersion.LowPart);
				int Build = LOWORD(dai.DriverVersion.LowPart);

				sprintf(tmp, "%s %s %d.%d.%d.%d", dai.Description, dai.Driver, Product, Version,
					SubVersion, Build);
			
				switch(dai.VendorId)
				{
				case 0x1002 :
					m_szVendorName = "ATI Technologies Inc.";
					break;
				case 0x10DE :
					m_szVendorName = "NVIDIA Corporation";
					break;
				case 0x102B : 
					m_szVendorName = "Matrox Electronic Systems Ltd.";
					break;
				case 0x121A :
					m_szVendorName = "3dfx Interactive Inc";
					break;
				case 0x5333 : 
					m_szVendorName = "S3 Graphics Co., Ltd.";
					break;
				case 0x8086 : 
					m_szVendorName = "Intel Corporation";
					break;
				default:
					{
						m_szVendorName = "Unknown VendorId: ";
						m_szVendorName += (unsigned int)dai.VendorId; 
					}
					break;
				}
			}

			//获取显示卡显示信息
			D3DDISPLAYMODE d3ddm;
			if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
				return 0;

			D3DPRESENT_PARAMETERS d3dpp;
			ZeroMemory(&d3dpp, sizeof(d3dpp));

			if (isFullScreen)
			{
				d3dpp.BackBufferWidth        = d3ddm.Width;
				d3dpp.BackBufferHeight       = d3ddm.Height;
				m_bbSize.w					 = d3ddm.Width;
				m_bbSize.h					 = d3ddm.Height;
			}
			else
			{
				d3dpp.BackBufferWidth        = bbSize.w;
				d3dpp.BackBufferHeight       = bbSize.h;
				m_bbSize.w					 = bbSize.w;
				m_bbSize.h					 = bbSize.h;
			}

			d3dpp.BackBufferFormat           = d3ddm.Format;
			d3dpp.BackBufferCount            = 1;
			d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
			d3dpp.MultiSampleQuality         = 0;
			d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
			d3dpp.hDeviceWindow              = hWnd;
			d3dpp.Windowed                   = !isFullScreen;
			d3dpp.EnableAutoDepthStencil     = 1; 
			d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
			d3dpp.Flags                      = 0;
			d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

			if (isVsvy)
				d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			else
				d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


			if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
				d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D32) == D3D_OK)
			{
				d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
				d3dpp.EnableAutoDepthStencil = TRUE;
			}
			else if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
				d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8) == D3D_OK)
			{
				d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
				d3dpp.EnableAutoDepthStencil = TRUE;
			}
			else if(m_pD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
				d3ddm.Format, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16) == D3D_OK)
			{
				d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
				d3dpp.EnableAutoDepthStencil = TRUE;
			}
			else
			{
				d3dpp.EnableAutoDepthStencil = 0;
			}

			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice)))
			{
				return 0;
			}

			setAlphaBlend(true);

			m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
			m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE);

			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
			m_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

			m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			m_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
			m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		}

		return true;
	}

	/**
	 *
	 * \param clrBack/* 
	 */
	void	D3D9RenderSystem::beginScene(const Colour clrBack/* =core::clrBLACK */)
	{
		if (SUCCEEDED(m_pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
			clrBack.color, 1.0f, 0)))
		{
			if (SUCCEEDED(m_pd3dDevice->BeginScene()))
			{
				setMatrix2D(0, 0, m_bbSize.w, m_bbSize.h);
			}	
		}
	}

	/**
	 *
	 */
	void	D3D9RenderSystem::endScene()
	{
		m_pd3dDevice->EndScene();
		m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
	}


	/**
	 *
	 * \param width 
	 * \param height 
	 */
	void	D3D9RenderSystem::setMatrix2D(
										const float w,
										const float h
										)
	{
		D3DXMATRIX project;
		D3DXMatrixScaling(&project, 1, -1, 0);
		
		D3DXMATRIX m;
		D3DXMatrixTranslation(&m, 0, h, 0);
		D3DXMatrixMultiply(&project, &project, &m);
		D3DXMatrixOrthoOffCenterLH(&m, 0, w, 0, h, 0, 1000);
		D3DXMatrixMultiply(&project, &project, &m);
		
		D3DXMATRIX view;	
		D3DXMatrixIdentity(&view);

		m_pd3dDevice->SetTransform(D3DTS_VIEW, &view);
		m_pd3dDevice->SetTransform(D3DTS_PROJECTION,
			&project);
	}

	/**
	 *
	 * \param x 
	 * \param y 
	 * \param w 
	 * \param h 
	 */
	void	D3D9RenderSystem::setMatrix2D(
										const float x, 
										const float y, 
										const float w, 
										const float h
										)
	{
		D3DXMATRIX project;
		D3DXMatrixScaling(&project, 1, -1, 0);

		D3DXMATRIX m;
		D3DXMatrixTranslation(&m, -x, y + h, 0);
		D3DXMatrixMultiply(&project, &project, &m);
		D3DXMatrixOrthoOffCenterLH(&m, 0, w, 0, h, 0, 1000);
		D3DXMatrixMultiply(&project, &project, &m);

		D3DXMATRIX view;	
		D3DXMatrixIdentity(&view);

		m_pd3dDevice->SetTransform(D3DTS_VIEW, &view);
		m_pd3dDevice->SetTransform(D3DTS_PROJECTION,
			&project);
	}

	/**
	 *
	 * \return 
	 */
	IDirect3DDevice9* D3D9RenderSystem::getD3DDevice() const
	{
		return m_pd3dDevice;
	}

	/**
	 *
	 * \param bOpen 
	 */
	void		D3D9RenderSystem::setAlphaBlend(bool bOpen)
	{
		if (bOpen)
		{
			m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
			m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		else
		{
			m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,  FALSE);
		}
	}

	/**
	 *
	 * \param dwMode 
	 */
	void		D3D9RenderSystem::setBlendMode(DWORD dwMode)
	{
		if((dwMode & BLEND_ALPHABLEND) != (m_curMode & BLEND_ALPHABLEND))
		{
			if(dwMode & BLEND_ALPHABLEND)
			{
				m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
			else
			{
				m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}
		}

		if((dwMode & BLEND_ZWRITE) != (m_curMode & BLEND_ZWRITE))
		{
			if(dwMode & BLEND_ZWRITE)
			{
				m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			}
			else 
			{
				m_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			}
		}			

		if((dwMode & BLEND_ADD) != (m_curMode & BLEND_ADD))
		{
			if(dwMode & BLEND_ADD)
			{
				m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
			}
			else
			{
				m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
			}
		}

		m_curMode = dwMode;
	}

	/**
	 *
	 * \param bOpen 
	 * \param clrKey 
	 */
	void		D3D9RenderSystem::setAlphaTest(
										bool bOpen, 
										const Colour clrKey
										)
	{
		if (bOpen)
		{
			m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE);
			m_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,  clrKey.color);
			m_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
		}
		else
		{
			m_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);
		}
	}

	/**
	 *
	 * \return 
	 */
	const Size&	D3D9RenderSystem::getBackBufferSize() const
	{
		return m_bbSize;
	}

	/**
	 *
	 * \param quad 
	 */
	void		D3D9RenderSystem::draw(const SQuad& quad)
	{
		
	}

	/**
	 *
	 * \param nLength 
	 * \return 
	 */
	Shape*		D3D9RenderSystem::createShape(int nLength)
	{
		return new D3D9Shape(this, nLength);
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Texture*	D3D9RenderSystem::createTextureFromFile(const String& szName)
	{
		// construct d3d9 texture object
		D3D9Texture* pTexture = new D3D9Texture(this);

		// if can't found file then throw execption
		if (!pTexture->createFromFile(szName))
		{
			// relase the bad texture memery
			dropAndNULL(pTexture);
			
			// create execption object
			tryException(EC_FILE_NOT_FOUND, "can't found texture file " + szName, 
				"D3D9RenderSystem::createTextureFromFile");
		}
		
		return pTexture;
	}
}