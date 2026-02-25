import cv2
import numpy as np
import stapipy as st

def acquire_image():
    try:
        # Initialize Stapipy API
        st.initialize()

        # Create a system object for device scan and connection
        st_system = st.create_system()
        # Connect to the first detected device (adjust as needed)
        st_device = st_system.create_first_device()

        # Display camera information
        print(f"Connected to device: {st_device.info.display_name}")

        # Create a data stream for handling image stream data
        st_datastream = st_device.create_datastream()
        

        # Start acquisition on host and camera
        st_datastream.start_acquisition()
        st_device.acquisition_start()

        print("Acquiring image...")

        # Retrieve the image buffer
        with st_datastream.retrieve_buffer() as st_buffer:
            if st_buffer.info.is_image_present:
                st_image = st_buffer.get_image()

                # Get raw image data
                data = st_image.get_image_data()

                # Convert to a numpy array
                pixel_format_info = st.get_pixel_format_info(st_image.pixel_format)
                if pixel_format_info.is_mono:
                    image = np.frombuffer(data, np.uint8).reshape(st_image.height, st_image.width)
                elif pixel_format_info.is_bayer:
                    nparr = np.frombuffer(data, np.uint8).reshape(st_image.height, st_image.width)
                    image = cv2.cvtColor(nparr, cv2.COLOR_BAYER_BG2RGB)
                else:
                    raise ValueError("Unsupported pixel format")

                # Display the image
                print("Image acquired successfully. Displaying...")
                cv2.imshow("Acquired Image", image)
                cv2.waitKey(0)
                cv2.destroyAllWindows()
            else:
                print("No image data found.")

        # Stop acquisition
        st_device.acquisition_stop()
        st_datastream.stop_acquisition()

    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    acquire_image()
