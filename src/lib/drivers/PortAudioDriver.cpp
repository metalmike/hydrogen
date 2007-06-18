
#include "PortAudioDriver.h"
#include "config.h"
#ifdef PORTAUDIO_SUPPORT

#include <iostream>

#include "lib/Preferences.h"

int portAudioCallback(
		void *inputBuffer,
		void *outputBuffer,
		unsigned long framesPerBuffer,
		PaTimestamp outTime,
		void *userData
		)
{
	PortAudioDriver *pDriver = (PortAudioDriver*)userData;
	pDriver->m_processCallback( pDriver->m_nBufferSize, NULL );

	float *out = (float*)outputBuffer;

	for( unsigned i = 0; i < framesPerBuffer; i++ ) {
		*out++ = pDriver->m_pOut_L[ i ];
		*out++ = pDriver->m_pOut_R[ i ];
	}
	return 0;
}



PortAudioDriver::PortAudioDriver(audioProcessCallback processCallback)
 : GenericDriver( "PortAudioDriver" )
 , m_processCallback( processCallback )
 , m_pOut_L( NULL )
 , m_pOut_R( NULL )
{
	infoLog( "INIT" );
	m_nBufferSize = Preferences::getInstance()->m_nBufferSize;
	m_nSampleRate = Preferences::getInstance()->m_nSampleRate;
}


PortAudioDriver::~PortAudioDriver()
{
	infoLog( "DESTROY" );
}

int PortAudioDriver::init(unsigned nBufferSize)
{
	infoLog( "INIT" );

	return 0;
}


int PortAudioDriver::connect()
{
	infoLog( "[connect]" );

	m_pOut_L = new float[ m_nBufferSize ];
	m_pOut_R = new float[ m_nBufferSize ];

	int err = Pa_Initialize();
	if( err != paNoError ) {
		errorLog( string( "Portaudio error: ").append( Pa_GetErrorText( err ) ) );
	}

	err = Pa_OpenDefaultStream(
			&m_pStream,        /* passes back stream pointer */
			0,              /* no input channels */
			2,              /* stereo output */
			paFloat32,      /* 32 bit floating point output */
			m_nSampleRate,          // sample rate
			m_nBufferSize,            // frames per buffer
			0,              // number of buffers, if zero then use default minimum
			portAudioCallback, /* specify our custom callback */
			this );        /* pass our data through to callback */
	if (err != paNoError) {
		errorLog( string( "Portaudio error: ").append( Pa_GetErrorText( err ) ) );
	}

	err = Pa_StartStream( m_pStream );
	if (err != paNoError) {
		errorLog( string( "Portaudio error: ").append( Pa_GetErrorText( err ) ) );
	}
	return 0;
}

void PortAudioDriver::disconnect()
{
	int err = Pa_StopStream( m_pStream );
	if (err != paNoError) {
		errorLog( string( "[disconnect] Err: ").append( Pa_GetErrorText( err ) ) );
	}

	err = Pa_CloseStream( m_pStream );
	if (err != paNoError) {
		errorLog( string( "[disconnect] Err: ").append( Pa_GetErrorText( err ) ) );
	}

	Pa_Terminate();

	delete[] m_pOut_L;
	m_pOut_L = NULL;

	delete[] m_pOut_R;
	m_pOut_R = NULL;
}

unsigned PortAudioDriver::getBufferSize()
{
	return m_nBufferSize;
}

unsigned PortAudioDriver::getSampleRate()
{
	return m_nSampleRate;
}

float* PortAudioDriver::getOut_L()
{
	return m_pOut_L;
}

float* PortAudioDriver::getOut_R()
{
	return m_pOut_R;
}

void PortAudioDriver::updateTransportInfo()
{
}

void PortAudioDriver::play()
{
	m_transport.m_status = TransportInfo::ROLLING;
}

void PortAudioDriver::stop()
{
	m_transport.m_status = TransportInfo::STOPPED;
}

void PortAudioDriver::locate( unsigned long nFrame )
{
	m_transport.m_nFrames = nFrame;
}

void PortAudioDriver::setBpm(float fBPM)
{
	m_transport.m_nBPM = fBPM;
}

#endif

