#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <linux/types.h>
#include <linux/videodev2.h>

int main(int argc, char **argv)
{
    int fd;
    struct v4l2_fmtdesc fmtdesc;
    struct v4l2_frmsizeenum fsenum;
    int fmt_index = 0;
    int frame_index = 0;

    if (argc != 2)
    {
        printf("Usage: %s </dev/videoX>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("can not open %s\n", argv[1]);
        return -1;
    }
    printf("Successfully opened %s (fd=%d)\n", argv[1], fd);

    while (1)
    {
        /* 枚举格式 - 使用 MULTIPLANAR 类型 */
        memset(&fmtdesc, 0, sizeof(struct v4l2_fmtdesc));
        fmtdesc.index = fmt_index;
        fmtdesc.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;  // 改为 MPLANE
        
        if (0 != ioctl(fd, VIDIOC_ENUM_FMT, &fmtdesc))
        {
            if (fmt_index == 0)
            {
                printf("Device does not support format enumeration. Error: %s\n", strerror(errno));
            }
            else
            {
                printf("No more formats at index %d\n", fmt_index);
            }
            break;
        }
        printf("Format %d: %s (pixelformat: 0x%08x)\n", fmt_index, fmtdesc.description, fmtdesc.pixelformat);

        frame_index = 0;
        while (1)
        {
            memset(&fsenum, 0, sizeof(struct v4l2_frmsizeenum));
            fsenum.pixel_format = fmtdesc.pixelformat;
            fsenum.index = frame_index;

            if (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &fsenum) == 0)
            {
                printf("  framesize %d: %d x %d\n", frame_index, fsenum.discrete.width, fsenum.discrete.height);
            }
            else
            {
                break;
            }

            frame_index++;
        }

        fmt_index++;
    }

    close(fd);
    return 0;
}