package main

import (
	"bufio"
	"fmt"
	"github.com/ziutek/mymysql/mysql"
	_ "github.com/ziutek/mymysql/native" // Native engine
	//"io"
	//"io/ioutil"
	"log"
	"os"
	"os/exec"
	"time"
)

func checkError(error error) {
	if error != nil {
		panic("ERROR: " + error.Error()) // terminate program
	}
}
func opendb() mysql.Conn {

	db := mysql.New("tcp", "", "127.0.0.1:3306", "root", "123456", "rfvid")

	err := db.Connect()
	if err != nil {
		panic(err)
	}
	return db

}

type RDSTAT struct {
	rdid     int
	ipreader string
	istat    int
}

var rdstat RDSTAT
var rdstats []RDSTAT

func getiprder() {
	for {
		db := opendb()

		res, err := db.Start("select * from reader")
		checkError(err)

		for {

			row, err := res.GetRow()
			checkError(err)

			if row == nil {
				// No more rows
				break
			}

			rdstat.rdid = row.Int(res.Map("id"))
			rdstat.ipreader = row.Str(res.Map("ipreader"))
			rdstat.istat = 0
			iflag := 0
			for _, item := range rdstats {
				if item.ipreader == rdstat.ipreader {
					iflag = 1
					break
				} else {
					iflag = 0

				}

			}
			if iflag == 0 {
				rdstats = append(rdstats, rdstat)
			}

		}
		time.Sleep(time.Second * 5)
		fmt.Println(rdstats)

		db.Close()
	}
}
func main() {
	getiprder()
	time.Sleep(time.Second * 50)
}

func service() {
	lf, err := os.OpenFile("angel.txt", os.O_CREATE|os.O_RDWR|os.O_APPEND, 0600)
	if err != nil {
		os.Exit(1)
	}
	defer lf.Close()

	// 日志
	l := log.New(lf, "", os.O_APPEND)

	for {
		cmd := exec.Command("cmdvideo.exe", "192.168.3.2")
		//cmd.Stdout = os.Stdout

		//cmd.Stderr = os.Stderr
		stdout, _ := cmd.StdoutPipe()

		err := cmd.Start()
		if err != nil {
			l.Printf("%s 启动命令失败", time.Now().Format("2006-01-02 15:04:05"), err)

			time.Sleep(time.Second * 5)
			continue
		}
		l.Printf("%s 进程启动", time.Now().Format("2006-01-02 15:04:05"), err)

		fileReader := bufio.NewReader(stdout)

		for {
			w, _ := fileReader.ReadString('\n')

			fmt.Printf(w)

		}

		err = cmd.Wait()
		l.Printf("%s 进程退出", time.Now().Format("2006-01-02 15:04:05"), err)

		time.Sleep(time.Second * 1)
	}
}
