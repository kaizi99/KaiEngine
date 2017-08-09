#pragma once

class DeferredRenderer
{
public:
	DeferredRenderer(int width, int height);

	void activateGeometryPass();
	void lightPass();
private:
	unsigned int m_gbuffer;
};