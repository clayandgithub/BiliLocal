#include "Common.h"
#include "WidgetPrivate.h"
#include "../../Local.h"
#include "../../UI/Interface.h"
#include <functional>

namespace
{
	class OWidget :public QOpenGLWidget
	{
	public:
		explicit OWidget(OpenGLOpaqueRenderPrivate *render) :
			QOpenGLWidget(lApp->findObject<Interface>()->widget()), render(render)
		{
			setAttribute(Qt::WA_TransparentForMouseEvents);
			lower();
			connect(this, &OWidget::frameSwapped, std::bind(&OpenGLRenderPrivate::onSwapped, render));
		}

	private:
		OpenGLOpaqueRenderPrivate *const render;

		void initializeGL()
		{
			render->initialize();
		}

		void paintGL()
		{
			render->paint(this);
		}
	};
}

OpenGLWidgetRenderPrivate::OpenGLWidgetRenderPrivate()
{
	widget = new OWidget(this);
}
