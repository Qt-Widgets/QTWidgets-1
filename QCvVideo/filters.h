#include <QDebug>

#include <cv.h>

class Filter
{
	public:
		enum Type {
			Rotation = 1,
			BrightnessContrast,
			Flip
		};

		// The "Virtual Constructor"
		static Filter *create(enum Filter::Type type);

		Filter()  {}
		virtual ~Filter() {}

		enum Filter::Type type() const { return m_type; }

		// Interface
		virtual void apply(cv::Mat *in, cv::Mat *out) = 0;
		virtual void setParameter(int param, QVariant value) = 0;

	protected:
		enum Filter::Type m_type;
};

class FlipFilter : public Filter
{
	public:
		FlipFilter();
		~FlipFilter();

		void apply(cv::Mat *in, cv::Mat *out);
		void setParameter(int param, QVariant value);

	private:
		bool m_vertical;
};

class RotateFilter : public Filter
{
	public:
		RotateFilter();
		~RotateFilter();

		void apply(cv::Mat *in, cv::Mat *out);
		void setParameter(int param, QVariant value);

	private:
		bool m_ccw;
		unsigned int m_count;
};

class BCFilter : public Filter
{
	public:
		BCFilter();
		~BCFilter();

		void apply(cv::Mat *in, cv::Mat *out);
		void setParameter(int param, QVariant value);

	private:
		double m_contrast;	// 1.0 - 3.0
		double m_brightness;	// 0 - 100
};

